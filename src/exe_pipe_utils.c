/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:01:36 by nspalevi          #+#    #+#             */
/*   Updated: 2025/01/29 07:20:51 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_child_commands(t_command *cmd_list)
{
	int	count;

	count = 0;
	while (cmd_list && cmd_list->atribute == CHILD)
	{
		count++;
		cmd_list = cmd_list->next;
	}
	return (count);
}

void	free_resources(t_pipe_resources *piping)
{
	free(piping->pipes);
	free(piping->pids);
	free(piping->status);
}

void	create_pipes(t_pipe_resources *piping)
{
	int	i;

	i = 0;
	while (i < piping->cmd_count - 1)
	{
		pipe(piping->pipes + i * 2);
		i++;
	}
}

void	close_pipes(t_pipe_resources *piping)
{
	int	i;

	i = 0;
	while (i < 2 * (piping->cmd_count - 1))
	{
		close(piping->pipes[i]);
		i++;
	}
}

void	free_command_resources(char **env, t_command *cmd_list,
		t_descriptor *descriptor)
{
	ft_free_array(env);
	free_commands(cmd_list);
	free_descriptor(descriptor);
}
