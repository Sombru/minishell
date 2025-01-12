/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:11:55 by pkostura          #+#    #+#             */
/*   Updated: 2025/01/12 21:34:47 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	handle_exit_arguments(char **args, int *exit_code)
{
	int	i;

	i = 1;
	if (args[i] != NULL)
	{
		if (is_numeric(args[i]))
			*exit_code = ft_atoi(args[i]);
		else
		{
			write(2, "exit: numeric argument required\n", 32);
			return (FAILURE);
		}
		i++;
	}
	if (args[i] != NULL)
	{
		write(2, "exit: too many arguments\n", 26);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_exit(char **args, char **env, t_descriptor *descriptor, t_command *commands)
{
	int	exit_code;

	exit_code = manage_exit_status(555);
	if (handle_exit_arguments(args, &exit_code))
		return (FAILURE);
	printf("terminated with status: %d\n", exit_code);
	// ft_free_array(args);
	ft_free_array(env);
	rl_clear_history();
	free_commands(commands);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	free_descriptor(descriptor);
	exit(exit_code);
	return (SUCCESS);
}
