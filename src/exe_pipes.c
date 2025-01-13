/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:05:03 by sombru            #+#    #+#             */
/*   Updated: 2025/01/13 18:12:54 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_parent_process;

int	pipe_commands(t_command *commands, char **env)
{
	t_command *cmd_list;
	int cmd_count;
	int *pipes;
	pid_t *pids;
	int i;
	int j;

	cmd_list = commands;
	cmd_count = 0;
	while (cmd_list)
	{
		cmd_count++;
		cmd_list = cmd_list->next;
	}
	if (DEBUG_MODE)
		printf("Command count: %d\n", cmd_count);
	pipes = malloc(sizeof(int) * 2 * (cmd_count - 1));
	pids = malloc(sizeof(pid_t) * cmd_count);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipe(pipes + i * 2);
		i++;
	}
	cmd_list = commands;
	i = 0;
	while (cmd_list)
	{
		pids[i] = fork();
		if (DEBUG_MODE)
			printf("Forked process with PID: %d\n", pids[i]);
		if (pids[i] == 0)
		{
			g_parent_process = 0;
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
			current_command(cmd_list, env);
			ft_free_array(env);
			free_commands(commands);
			free(pipes);
			free(pids);
			exit(manage_exit_status(0));
		}
		cmd_list = cmd_list->next;
		i++;
	}
	i = 0;
	while (i < 2 * (cmd_count - 1))
		close(pipes[i++]);
	i = 0;
	while (i < cmd_count)
		waitpid(pids[i++], NULL, 0);
	free(pipes);
	free(pids);
	return (0);
}
