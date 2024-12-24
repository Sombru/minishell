/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:08:57 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/22 21:45:07 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(char **args, char **env)
{
	int	i;

	if (args[1] != NULL)
	{
		write(STDERR_FILENO, "env: too many arguments\n", 25);
		return (FAILURE);
	}
	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (SUCCESS);
}
