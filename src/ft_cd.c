/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:01:12 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/24 19:08:15 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <limits.h>

int	ft_cd(char **args, char **env)
{
	char	*home_dir;
	int		temp;

	home_dir = ft_getenv("HOME", env);
	if (args[1] == NULL)
	{
		if (!home_dir)
		{
			write(2, "cd: HOME not set\n", 17);
			return (FAILURE);
		}
		temp = chdir(home_dir);
		if (temp == -1)
			return (FAILURE);
		return (SUCCESS);
	}
	if (args[2] != NULL)
	{
		write(2, "cd: too many arguments\n", 24);
		return (FAILURE);
	}
	if (chdir(args[1]) == -1)
		return (write(2, "cd: no such file or directory\n", 30));
	return (SUCCESS);
}
