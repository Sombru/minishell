/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 23:12:34 by sombru            #+#    #+#             */
/*   Updated: 2024/12/27 12:48:00 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int handle_child(t_command *current, t_command *commands, t_descriptor *descriptor, char **env)
{
	t_redirections  *redirections;
	int			 	redir_status;
	char			**args_copy;
	
    redir_status = 0;
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
        dup2(descriptor->prev_fd, STDIN_FILENO);
    if (!is_output_redirection(redirections))
        dup2(descriptor->pipefd[1], STDOUT_FILENO);
    close(descriptor->pipefd[0]);
    close(descriptor->pipefd[1]);
    close(descriptor->prev_fd);
    if (redir_status == -1)
        return (FAILURE);
    args_copy = ft_arrcpy(current->arguemnts);
    free_redirections(redirections);
    free_commands(commands);
    free(descriptor);
    exit(execute_command(args_copy, env));
}
