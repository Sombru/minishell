/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:05:03 by sombru            #+#    #+#             */
/*   Updated: 2025/01/29 13:34:07 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	setup_pipes(t_pipe_resources *piping, int i)
{
	if (i > 0)
		dup2(piping->pipes[(i - 1) * 2], STDIN_FILENO);
	if (i < piping->cmd_count - 1)
		dup2(piping->pipes[i * 2 + 1], STDOUT_FILENO);
}

int	wait_for_children(t_pipe_resources *piping)
{
	int	status;
	int	termiate;
	int	i;

	status = 0;
	termiate = 0;
	i = 0;
	while (i < piping->cmd_count)
	{
		waitpid(piping->pids[i], &piping->status[i], 0);
		piping->status[i] = WEXITSTATUS(piping->status[i]);
		if (piping->status[i] != 0)
			status = piping->status[i];
		if (piping->status[i] == 130)
			termiate = 130;
		i++;
	}
	if (termiate)
		return (termiate);
	return (status);
}

static void	handle_child_process(t_pipe_resources *piping, t_command *cmd_list,
		char **env)
{
	t_descriptor	*descriptor;

	no_nl(true);
	setup_pipes(piping, piping->current_cmd);
	if (handle_redirections(cmd_list, &descriptor, env) == SUCCESS)
	{
		close_pipes(piping);
		g_status(execute_command(cmd_list->arguemnts, env, descriptor,
				cmd_list));
		free_command_resources(env, cmd_list, descriptor);
		free_resources(piping);
	}
	else
	{
		close_pipes(piping);
		free_command_resources(env, cmd_list, descriptor);
		free_resources(piping);
	}
	exit(g_status(555));
}

static void	initialize_pipe_resources(t_pipe_resources *piping,
		t_command *cmd_list)
{
	piping->cmd_count = count_child_commands(cmd_list) + 1;
	piping->pipes = malloc(sizeof(int) * 2 * (piping->cmd_count - 1));
	piping->status = malloc(sizeof(int) * 2 * (piping->cmd_count));
	piping->pids = malloc(sizeof(pid_t) * piping->cmd_count);
	piping->current_cmd = 0;
}

int	pipe_commands(t_command **commands, char **env)
{
	t_command			*cmd_list;
	t_pipe_resources	piping;
	int					status;

	cmd_list = *commands;
	initialize_pipe_resources(&piping, cmd_list);
	create_pipes(&piping);
	cmd_list = *commands;
	while (cmd_list && piping.current_cmd < piping.cmd_count)
	{
		piping.pids[piping.current_cmd] = fork();
		if (piping.pids[piping.current_cmd] == 0)
			handle_child_process(&piping, cmd_list, env);
		cmd_list = cmd_list->next;
		piping.current_cmd++;
	}
	signal(SIGINT, handle_sigint_parent);
	close_pipes(&piping);
	status = wait_for_children(&piping);
	no_nl(false);
	free_resources(&piping);
	*commands = cmd_list;
	return (status);
}
