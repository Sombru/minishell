/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:40:34 by nspalevi          #+#    #+#             */
/*   Updated: 2025/01/03 13:04:39 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**store_environment(char **env)
{
	char	**new_env;
	int		i;
	int		count;

	count = 0;
	while (env[count])
		count++;
	new_env = malloc((count + MAX_ENV_SIZE) * sizeof *new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

static bool	is_valid_var_name(char *name)
{
	int	i;

	i = 0;
	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char	*concat_env_var(char *name, char *value)
{
	char	*new_var;
	int		name_len;
	int		value_len;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	new_var = malloc(name_len + value_len + 2);
	if (!new_var)
		return (NULL);
	ft_strcpy(new_var, name);
	new_var[name_len] = '=';
	ft_strcpy(new_var + name_len + 1, value);
	return (new_var);
}

int	ft_setenv(char *name, char *value, char **env)
{
	int		i;
	int		name_len;
	char	*new_var;

	i = 0;
	name_len = ft_strlen(name);
	if (!is_valid_var_name(name))
		return (-1);
	new_var = concat_env_var(name, value);
	if (!new_var)
		return (-1);
	while (env[++i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			free(env[i]);
			env[i] = new_var;
			return (0);
		}
	}
	if (!env)
		return (1);
	env[i] = new_var;
	env[i + 1] = NULL;
	return (0);
}

char	*ft_getenv(const char *name, char **env)
{
	size_t	name_len;
	int		i;

	if (!name || !env)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			return (&env[i][name_len + 1]);
		}
		i++;
	}
	return (NULL);
}
