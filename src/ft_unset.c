/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:04:23 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/17 19:12:15 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	remove_env_var(char **env, int index)
{
	free(env[index]);
	while (env[index] != NULL)
	{
		env[index] = env[index + 1];
		index++;
	}
}

int	ft_unset(char **args, char **env)
{
	int	i;
	int	j;

	if (args[1] == NULL)
	{
		write(2, "unset: missing argument\n", 24);
		return (FAILURE);
	}
	i = 1;
	while (args[i] != NULL)
	{
		j = 0;
		while (env[j] != NULL)
		{
			if (ft_strncmp(env[j], args[i], ft_strlen(args[i])) == 0
				&& env[j][ft_strlen(args[i])] == '=')
			{
				remove_env_var(env, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
