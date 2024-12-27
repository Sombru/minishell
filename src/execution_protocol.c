/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_protocol.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 00:47:46 by sombru            #+#    #+#             */
/*   Updated: 2024/12/27 12:47:31 by sombru           ###   ########.fr       */
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

t_descriptor *get_descriptors(void)
{
    t_descriptor *descriptor;

    int						original_fds[2];
    int						prev_fd;

    descriptor = malloc(sizeof(t_descriptor));
    original_fds[0] = dup(STDIN_FILENO);
    original_fds[1] = dup(STDOUT_FILENO);
    prev_fd = dup(STDIN_FILENO);
    descriptor->original_fds[0] = original_fds[0];
    descriptor->original_fds[1] = original_fds[1];
    descriptor->prev_fd = prev_fd;
    return (descriptor);
}

static int current_command(t_command *current, t_descriptor *descriptor, char **env)
{
    t_redirections  *redirections;
    int             redir_status;
    
    redirections = find_redirections(current->arguemnts);
    if (redirections && ft_strcmp(redirections->type, HEREDOC) == 0)
        dup2(descriptor->original_fds[0], STDOUT_FILENO);
    else
        dup2(descriptor->prev_fd, STDIN_FILENO);
    close(descriptor->prev_fd);
    if (redirections)
    {
        redir_status = apply_redirections(redirections, env);
        current->arguemnts = reparse_args(current->arguemnts, count_args(current->arguemnts));
        free_redirections(redirections);
    }
    if (redir_status == -1)
    {
        perror("redirections");
        return (FAILURE);
    }
    manage_exit_status(execute_command(current->arguemnts, env));
    dup2(descriptor->original_fds[0], STDIN_FILENO);
    dup2(descriptor->original_fds[1], STDOUT_FILENO);
    return (SUCCESS);
}

int	execution_protocol(t_command *commands, char **env)
{
    t_command       *current;
    t_descriptor    *descriptor;
    pid_t           pid;
    int             status;

    current = commands;
    descriptor = get_descriptors();
    while (current)
    {
        while (current && current->atribute == CHILD)
        {
            if (pipe(descriptor->pipefd) == -1)
                return (FAILURE);
            pid = fork();
            if (pid == 0)
                handle_child(current, commands, descriptor, env);   
            else if (pid > 0)
            {
                signal(SIGINT, SIG_IGN);
                waitpid(pid, &status, 0);
                handle_parent(descriptor);
                current = current->next;
            }
            else
                return (FAILURE);
        }
        if (current)
        {
            if (current_command(current, descriptor, env) == FAILURE)
                return (FAILURE);
            if (current->atribute == CMDOR && manage_exit_status(555) == 0)
                return (SUCCESS);
            current = current->next;
        }
    }
    close(descriptor->original_fds[0]);
    close(descriptor->original_fds[1]);
    free(descriptor);
    return (SUCCESS);
}

int execute_command(char **args, char **env)
{
    char    *tmp;

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
    tmp = ft_strjoin(args[0], "'\n"RST);
	ft_putstr_fd(tmp, STDERR_FILENO);
    free(tmp);
	return (COMMAND_NOT_FOUND);
}
