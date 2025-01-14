/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:05:03 by sombru            #+#    #+#             */
/*   Updated: 2025/01/14 13:14:07 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_commands(t_command **commands, char **env)
{
	t_command		*cmd_list;
	t_descriptor	*descriptor;
	int				cmd_count;
	int				*pipes;
	pid_t			*pids;
	int				*status;
	int				ret;
	int				i;
	int				j;

	cmd_count = 0;
	ret = SUCCESS;
	cmd_list = *commands;
	while (cmd_list && cmd_list->atribute == CHILD)
	{
		cmd_count++;
		cmd_list = cmd_list->next;
	}
	cmd_count++;
	if (DEBUG_MODE)
		printf("Command count: %d\n", cmd_count);
	pipes = malloc(sizeof(int) * 2 * (cmd_count - 1));
	status = malloc(sizeof(int) * 2 * (cmd_count));
	pids = malloc(sizeof(pid_t) * cmd_count);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipe(pipes + i * 2);
		i++;
	}
	i = 0;
	cmd_list = *commands;
	while (cmd_list && i < cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (handle_redirections(cmd_list, &descriptor, env) == SUCCESS)
			{
				if (i > 0)
					dup2(pipes[(i - 1) * 2], STDIN_FILENO);
				if (i < cmd_count - 1)
					dup2(pipes[i * 2 + 1], STDOUT_FILENO);
				j = 0;
				while (j < 2 * (cmd_count - 1))
				{
					close(pipes[j]);
					j++;
				}
				execute_command(cmd_list->arguemnts, env, descriptor, cmd_list);
				ft_free_array(env);
				free_commands(cmd_list);
				free(pipes);
				free(pids);
				free(status);
				free_descriptor(descriptor);
				exit(manage_exit_status(555));
			}
			else
			{
				ft_free_array(env);
				free_commands(cmd_list);
				free(pipes);
				free(pids);
				free(status);
				free_descriptor(descriptor);
				exit(manage_exit_status(555));
			}
		}
		if (DEBUG_MODE)
			printf("Forked process with PID: %d\n", pids[i]);
		cmd_list = cmd_list->next;
		i++;
	}
	i = 0;
	signal(SIGINT, handle_sigint_child);
	while (i < 2 * (cmd_count - 1))
		close(pipes[i++]);
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status[i], 0);
		if (WTERMSIG(status[i] != 0))
		{
			ret = manage_exit_status(WTERMSIG(status[i]));
		}
		i++;
	}
	free(pipes);
	free(pids);
	free(status);
	*commands = cmd_list;
	return (manage_exit_status(ret));
}
