/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_protocol.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 00:47:46 by sombru            #+#    #+#             */
/*   Updated: 2025/01/14 11:34:33 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_redirections(t_command *command, t_descriptor **descriptor, char **env)
{
	t_redirections	*redirections;
	int				redir_status;

	redir_status = 0;
	(*descriptor) = get_descriptors();
	redirections = find_redirections(command->arguemnts);
	if (redirections)
	{
		redir_status = apply_redirections(redirections, env);
		command->arguemnts = reparse_args(command->arguemnts,
				ft_count_args(command->arguemnts));
		free_redirections(redirections);
	}
	return (manage_exit_status(redir_status));
}

int	execution_protocol(t_command *commands, char **env)
{
	t_descriptor	*descriptor;
	while (commands)
	{
		if (commands && commands->atribute == CHILD)
		{
			if (pipe_commands(&commands, env) != 0)
				break ;
		}
		else
		{
			if(handle_redirections(commands, &descriptor, env) == SUCCESS)
				manage_exit_status(execute_command(commands->arguemnts, env, descriptor, commands));
			free_descriptor(descriptor);
			commands = commands->next;
		}
		if (!commands)
			break ;
		if (commands && commands->prev->atribute == CMDOR && manage_exit_status(555) == 0)
			break ;
	}
	return (SUCCESS);
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
