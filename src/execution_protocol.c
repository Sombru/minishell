/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_protocol.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 00:47:46 by sombru            #+#    #+#             */
/*   Updated: 2024/12/24 22:15:49 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int count_args(char **args)
{
    int count;

    count = 0;
    while (args[count])
        count++;
    return (count);
}

static int  is_output_redirection(t_redirections *redirections)
{
   while (redirections)
   {
        if (ft_strcmp(redirections->type, STDOUT) == 0)
           return (1);
        if (ft_strcmp(redirections->type, APPEND) == 0)
           return (1);
       redirections = redirections->next;
   }
   return (0);
   
}

static int is_input_redirection(t_redirections *redirections)
{
    while (redirections)
    {
        if (ft_strcmp(redirections->type, STDIN) == 0)
            return (1);
        if (ft_strcmp(redirections->type, HEREDOC) == 0)
            return (1);
        redirections = redirections->next;
    }
    return (0);
}

int	execution_protocol(t_command *commands, char **env)
{
    t_command       *current;
    t_redirections  *redirections;
    int             original_fds[2];
    int             prev_fd;
    pid_t           pid;
    int             status;
    int             pipefd[2];
    int             redir_status;

    original_fds[0] = dup(STDIN_FILENO);
    original_fds[1] = dup(STDOUT_FILENO);
    prev_fd = dup(STDIN_FILENO);
    current = commands;

    while (current)
    {
        redir_status = 0;
        while (current && current->atribute == CHILD)
        {
            if (pipe(pipefd) == -1)
            {
                perror("pipe");
                break;
            }

            pid = fork();
            if (pid == 0)
            {
                
                if (DEBUG_MODE)
                {
                    ft_putstr_fd("Child process: ", STDERR_FILENO);
                    print_args(current->arguemnts);
                }
                redirections = find_redirections(current->arguemnts);
                if (redirections)
                {
                    redir_status =  apply_redirections(redirections, env);
                    current->arguemnts = reparse_args(current->arguemnts, count_args(current->arguemnts));
                }

                if (!is_input_redirection(redirections))
                    dup2(prev_fd, STDIN_FILENO);
                if (!is_output_redirection(redirections))
                    dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
                close(prev_fd);
                if (redir_status == -1)
                    break;
                free_redirections(redirections);
                exit(execute_command(current->arguemnts, env));
            }
            else if (pid > 0)
            {
                signal(SIGINT, SIG_IGN);
                close(pipefd[1]);
                waitpid(pid, &status, 0);
                close(prev_fd);
                prev_fd = pipefd[0];

                dup2(original_fds[0], STDIN_FILENO);
                dup2(original_fds[1], STDOUT_FILENO);

                current = current->next;
            }
            else
            {
                perror("fork");
                break;
            }
        }
        if (current)
        {
            dup2(prev_fd, STDIN_FILENO);
            close(prev_fd);

            redirections = find_redirections(current->arguemnts);
            if (redirections)
            {
                redir_status = apply_redirections(redirections, env);
                current->arguemnts = reparse_args(current->arguemnts, count_args(current->arguemnts));
                free_redirections(redirections);
            }
            if (redir_status == -1)
                break;
            manage_exit_status(execute_command(current->arguemnts, env));
            dup2(original_fds[0], STDIN_FILENO);
            dup2(original_fds[1], STDOUT_FILENO);
            if (current->atribute == CMDOR && manage_exit_status(555) == 0)
                break;
            current = current->next;
        }
    }
    close(original_fds[0]);
    close(original_fds[1]);
    return (0);
}

int execute_command(char **args, char **env)
{
    if (args[0] == NULL)
        return (SUCCESS);
	else if (ft_strcmp(args[0], ECHO_CMD) == 0)
		return (ft_echo(args));
	else if (ft_strcmp(args[0], CD) == 0)
		return (ft_cd(args, env));
	else if (ft_strcmp(args[0], PWD) == 0)
		return (ft_pwd(args));
	else if (ft_strcmp(args[0], EXPORT) == 0)
		return (ft_export(args, env));
	else if (ft_strcmp(args[0], UNSET) == 0)
		return (ft_unset(args, env));
	else if (ft_strcmp(args[0], ENV) == 0)
		return (ft_env(args, env));
	else if (ft_strcmp(args[0], EXIT) == 0)
		return (ft_exit(args, env));
	else if (is_bin_command(args[0]))
		return(execute_bin_command(args, env));
	ft_putstr_fd(RED "minishell:" RST" command not found: "RED"`" , STDERR_FILENO);
	ft_putstr_fd(ft_strjoin(args[0], "'\n"RST), STDERR_FILENO);
	return (COMMAND_NOT_FOUND);
}
