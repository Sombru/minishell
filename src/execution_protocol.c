/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_protocol.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 00:47:46 by sombru            #+#    #+#             */
/*   Updated: 2025/01/09 11:23:02 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_descriptor	*get_descriptors(void)
{
	t_descriptor	*descriptor;
	int				original_fds[2];
	int				prev_fd;

	descriptor = malloc(sizeof(t_descriptor));
	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
	prev_fd = dup(STDIN_FILENO);
	descriptor->original_fds[0] = original_fds[0];
	descriptor->original_fds[1] = original_fds[1];
	descriptor->prev_fd = prev_fd;
	return (descriptor);
}

static void	free_descriptor(t_descriptor *descriptor)
{
	close(descriptor->original_fds[0]);
	close(descriptor->original_fds[1]);
	free(descriptor);
}

int	execution_protocol(t_command *commands, char **env,
		t_descriptor *descriptor)
{
	t_command	*current;
	int			status;

	current = commands;
	while (current)
	{
		while (current && current->atribute == CHILD)
		{
			status = handle_pipes(current, commands, descriptor, env);
			if (status == FAILURE)
				break ;
			current = current->next;
		}
		if (current)
		{
			if (current_command(current, descriptor, env) == FAILURE)
				break ;
			if (current->atribute == CMDOR && manage_exit_status(555) == 0)
				break ;
			current = current->next;
		}
	}
	free_descriptor(descriptor);
	return (SUCCESS);
}

int	current_command(t_command *current, t_descriptor *descriptor, char **env)
{
	t_redirections	*redirections;
	int				redir_status;

	redir_status = 0;
	redirections = find_redirections(current->arguemnts);
	if (redirections && ft_strcmp(redirections->type, HEREDOC) == 0)
		dup2(descriptor->original_fds[0], STDOUT_FILENO);
	else
		dup2(descriptor->prev_fd, STDIN_FILENO);
	if (redirections)
	{
		redir_status = apply_redirections(redirections, env);
		current->arguemnts = reparse_args(current->arguemnts,
				ft_count_args(current->arguemnts));
		free_redirections(redirections);
	}
	if (redir_status == FAILURE)
		return (FAILURE);
	manage_exit_status(execute_command(current->arguemnts, env));
	dup2(descriptor->original_fds[0], STDIN_FILENO);
	dup2(descriptor->original_fds[1], STDOUT_FILENO);
	return (SUCCESS);
}

int	execute_command(char **args, char **env)
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
	else
		return (execute_bin_command(args, env));
}
