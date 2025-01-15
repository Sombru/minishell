/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:01:36 by nspalevi          #+#    #+#             */
/*   Updated: 2025/01/15 10:07:48 by nspalevi         ###   ########.fr       */
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

void	free_resources(t_pipe_resources *res)
{
	free(res->pipes);
	free(res->pids);
	free(res->status);
}

void	create_pipes(t_pipe_resources *res)
{
	int	i;

	i = 0;
	while (i < res->cmd_count - 1)
	{
		pipe(res->pipes + i * 2);
		i++;
	}
}

void	close_pipes(t_pipe_resources *res)
{
	int	i;

	i = 0;
	while (i < 2 * (res->cmd_count - 1))
	{
		close(res->pipes[i]);
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
