/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:03:07 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/17 15:02:37 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_export_argument(char *arg, char **env)
{
	char	*equal_sign;
	char	*name;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		name = arg;
		value = equal_sign + 1;
	}
	else
	{
		name = arg;
		value = "";
	}
	if (ft_setenv(name, value, env) == -1)
	{
		if (equal_sign)
			*equal_sign = '=';
		printf("export: error\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_export(char **args, char **env)
{
	int	i;

	i = 0;
	if (args[1] == NULL)
	{
		while (env[i] != NULL)
		{
			printf("%s\n", env[i]);
			i++;
		}
		return (SUCCESS);
	}
	i = 1;
	while (args[i] != NULL)
	{
		if (handle_export_argument(args[i], env) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
