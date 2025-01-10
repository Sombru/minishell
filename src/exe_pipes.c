/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:05:03 by sombru            #+#    #+#             */
/*   Updated: 2025/01/10 13:28:44 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exit_child(t_descriptor *descriptor, t_redirections *redirections,
		t_command *commands)
{
	close(descriptor->pipefd[0]);
	close(descriptor->pipefd[1]);
	close(descriptor->prev_fd);
	free(descriptor);
	free_redirections(redirections);
	free_commands(commands);
	exit(FAILURE);
}

static void	cleanup_child(t_redirections *redirections, t_command *commands,
		t_descriptor *descriptor)
{
	free_redirections(redirections);
	free_commands(commands);
	free(descriptor);
}

int	stdin_required(char *command)
{
	const char	*stdin_commands[] = {"cat", "grep", "awk", "wc", "sort", "sleep", NULL};
	int			i;

	i = 0;
	while (stdin_commands[i])
	{
		if (ft_strcmp(command, stdin_commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	handle_pipes(t_command *current, t_command *commands,
		t_descriptor *descriptor, char **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(descriptor->pipefd) == -1)
		return (FAILURE);
	pid = fork();
	if (pid == 0)
		status = handle_child(current, commands, descriptor, env);
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		if (!stdin_required(current->arguemnts[0]))
			waitpid(pid, &status, 0);
		handle_parent(descriptor);
	}
	else if (status == FAILURE)
		return (FAILURE);
	return (status);
}

int	handle_child(t_command *current, t_command *commands,
		t_descriptor *descriptor, char **env)
{
	t_redirections	*redirections;
	int				redir_status;
	char			**args_copy;

	redir_status = 0;
	signal(SIGINT, handle_sigint_child);
	redirections = find_redirections(current->arguemnts);
	if (redirections)
	{
		redir_status = apply_redirections(redirections, env);
		current->arguemnts = reparse_args(current->arguemnts,
				ft_count_args(current->arguemnts));
	}
	if (redir_status == FAILURE)
		exit_child(descriptor, redirections, commands);
	if (!is_input_redirection(redirections))
		dup2(descriptor->prev_fd, STDIN_FILENO);
	if (!is_output_redirection(redirections))
		dup2(descriptor->pipefd[1], STDOUT_FILENO);
	args_copy = ft_arrcpy(current->arguemnts);
	close(descriptor->pipefd[0]);
	close(descriptor->pipefd[1]);
	close(descriptor->prev_fd);
	cleanup_child(redirections, commands, descriptor);
	exit(execute_command(args_copy, env));
}

int	handle_parent(t_descriptor *descriptor)
{
	close(descriptor->pipefd[1]);
	close(descriptor->prev_fd);
	descriptor->prev_fd = descriptor->pipefd[0];
	dup2(descriptor->original_fds[0], STDIN_FILENO);
	dup2(descriptor->original_fds[1], STDOUT_FILENO);
	return (SUCCESS);
}
