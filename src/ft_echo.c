/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:13:47 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/18 23:38:00 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_argument(const char *arg, int *n_option, int last_arg)
{
	if (ft_strcmp(arg, "-n") == 0)
	{
		*n_option = 1;
	}
	else
	{
		write(STDOUT_FILENO, arg, ft_strlen(arg));
		if (last_arg != 69)
			write(STDOUT_FILENO, " ", 1);
	}
}

int	ft_echo(char **args)
{
	int	n_option;
	int	i;
	int	last_arg;

	n_option = 0;
	last_arg = 0;
	i = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	while (args[i])
	{
		if (args[i +1] == NULL)
			last_arg = 69;
		handle_argument(args[i], &n_option, last_arg);
		i++;
	}
	if (n_option == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
