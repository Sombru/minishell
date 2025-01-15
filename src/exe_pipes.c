/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:05:03 by sombru            #+#    #+#             */
/*   Updated: 2025/01/15 13:05:24 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	setup_pipes(t_pipe_resources *res, int i)
{
	if (i > 0)
		dup2(res->pipes[(i - 1) * 2], STDIN_FILENO);
	if (i < res->cmd_count - 1)
		dup2(res->pipes[i * 2 + 1], STDOUT_FILENO);
}

static void	wait_for_children(t_pipe_resources *res, int *ans)
{
	int	i;

	i = 0;
	while (i < res->cmd_count)
	{
		waitpid(res->pids[i], &res->status[i], 0);
		if (WTERMSIG(res->status[i]) != 0)
			*ans = manage_exit_status(WTERMSIG(res->status[i]));
		i++;
	}
}

static void	handle_child_process(t_pipe_resources *res, t_command *cmd_list,
		char **env)
{
	t_descriptor	*descriptor;

	no_nl(true);
	setup_pipes(res, res->current_cmd);
	if (handle_redirections(cmd_list, &descriptor, env) == SUCCESS)
	{
		close_pipes(res);
		execute_command(cmd_list->arguemnts, env, descriptor, cmd_list);
		free_command_resources(env, cmd_list, descriptor);
		free_resources(res);
	}
	else
	{
		close_pipes(res);
		free_command_resources(env, cmd_list, descriptor);
		free_resources(res);
	}
	exit(manage_exit_status(555));
}

static void	initialize_pipe_resources(t_pipe_resources *res,
		t_command *cmd_list)
{
	res->cmd_count = count_child_commands(cmd_list) + 1;
	res->pipes = malloc(sizeof(int) * 2 * (res->cmd_count - 1));
	res->status = malloc(sizeof(int) * 2 * (res->cmd_count));
	res->pids = malloc(sizeof(pid_t) * res->cmd_count);
	res->current_cmd = 0;
}

int	pipe_commands(t_command **commands, char **env)
{
	t_command			*cmd_list;
	t_pipe_resources	res;
	int					ans;

	ans = SUCCESS;
	cmd_list = *commands;
	initialize_pipe_resources(&res, cmd_list);
	create_pipes(&res);
	cmd_list = *commands;
	while (cmd_list && res.current_cmd < res.cmd_count)
	{
		res.pids[res.current_cmd] = fork();
		if (res.pids[res.current_cmd] == 0)
			handle_child_process(&res, cmd_list, env);
		cmd_list = cmd_list->next;
		res.current_cmd++;
	}
	signal(SIGINT, handle_sigint_parent);
	close_pipes(&res);
	wait_for_children(&res, &ans);
	no_nl(false);
	free_resources(&res);
	*commands = cmd_list;
	return (manage_exit_status(ans));
}
