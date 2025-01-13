/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_protocol.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 00:47:46 by sombru            #+#    #+#             */
/*   Updated: 2025/01/13 17:55:38 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execution_protocol(t_command *commands, char **env)
{
	int			exit_status;
	t_command	*pipeline;
	int			cmd_count;

	exit_status = SUCCESS;
	while (commands)
	{
		pipeline = commands;
		cmd_count = 0;
		while (pipeline && pipeline->atribute != CMDAND
			&& pipeline->atribute != CMDOR)
		{
			cmd_count++;
			pipeline = pipeline->next;
		}
		if (cmd_count > 1)
			exit_status = pipe_commands(commands, env);
		else
			exit_status = current_command(commands, env);
		commands = pipeline;
		if (commands)
		{
			if (commands->atribute == CMDAND)
			{
				if (exit_status != SUCCESS)
					commands = commands->next;
			}
			else if (commands->atribute == CMDOR)
			{
				if (exit_status == SUCCESS)
					commands = commands->next;
			}
			commands = commands->next;
		}
	}
	return (exit_status);
}

int	current_command(t_command *command, char **env)
{
	t_redirections	*redirections;
	t_descriptor	*descriptor;
	int				redir_status;
	int				status;

	redir_status = 0;
	descriptor = get_descriptors();
	redirections = find_redirections(command->arguemnts);
	if (redirections)
	{
		redir_status = apply_redirections(redirections, env);
		command->arguemnts = reparse_args(command->arguemnts,
				ft_count_args(command->arguemnts));
		free_redirections(redirections);
	}
	if (redir_status == FAILURE)
	{
		manage_exit_status(FAILURE);
		free_descriptor(descriptor);
		return (manage_exit_status(FAILURE));
	}
	status = execute_command(command->arguemnts, env, descriptor, command);
	manage_exit_status(status);
	free_descriptor(descriptor);
	return (manage_exit_status(status));
}

int	execute_command(char **args, char **env, t_descriptor *descriptor,
		t_command *commands)
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
		return (ft_exit(args, env, descriptor, commands));
	else
		return (execute_bin_command(args, env, descriptor, commands));
}
