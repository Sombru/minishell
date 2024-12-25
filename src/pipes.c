/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 23:12:34 by sombru            #+#    #+#             */
/*   Updated: 2024/12/25 23:08:31 by pasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int count_args(char **args)
{
    int count = 0;
    while (args[count])
        count++;
    return (count);
}

int handle_pipe(t_command *current, int prev_fd, int original_fds[2], char **env, t_command *commands)
{
    int pipefd[2];
    pid_t pid;
    int status;
    int redir_status = 0;
    t_redirections *redirections;
    char **args_copy;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (-1);
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
            redir_status = apply_redirections(redirections, env);
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
            exit(EXIT_FAILURE);
        args_copy = ft_arrcpy(current->arguemnts);
        free_redirections(redirections);
        free_commands(commands);
        exit(execute_command(args_copy, env));
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

        return (prev_fd);
    }
    else
    {
        perror("fork");
        return (-1);
    }
    return (prev_fd);
}
