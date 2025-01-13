/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_protocol.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 00:47:46 by sombru            #+#    #+#             */
/*   Updated: 2025/01/13 16:50:41 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execution_protocol(t_command *commands, char **env)
{
	t_command	*tmp;
	int			cmd_count;

	tmp = commands;
	cmd_count = 0;
	while (tmp)
	{
		cmd_count++;
		tmp = tmp->next;
	}
	if (cmd_count > 1)
		return (pipe_commands(commands, env));
	while (commands)
	{
		current_command(commands, env);
		if (commands->atribute == CMDOR && manage_exit_status(555) == 0)
			break ;
		commands = commands->next;
	}
	return (SUCCESS);
}

int	current_command(t_command *command, char **env)
{
	t_redirections	*redirections;
	t_descriptor	*descriptor;
	int				redir_status;

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
		return (manage_exit_status(FAILURE));
	manage_exit_status(execute_command(command->arguemnts, env, descriptor,
			command));
	free_descriptor(descriptor);
	return (manage_exit_status(555));
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
