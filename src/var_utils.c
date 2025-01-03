/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 01:41:43 by sombru            #+#    #+#             */
/*   Updated: 2025/01/03 13:26:12 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_var(char **input, char **env)
{
	char	*var_name;
	char	*var_value;
	int		len;
	char	*start;

	(*input)++;
	if (**input == '?')
	{
		(*input)++;
		return (ft_itoa(manage_exit_status(555)));
	}
	if (**input == '\0' || isspace(**input) || !ft_isalnum(**input))
		return (ft_strdup("$"));
	start = *input;
	while (**input && (ft_isalnum(**input) || **input == '_'))
		(*input)++;
	len = *input - start;
	var_name = strndup(start, len);
	if (!var_name || !ft_strcmp(var_name, ""))
		return (NULL);
	var_value = ft_getenv(var_name, env);
	free(var_name);
	if (!var_value)
		return (NULL);
	return (ft_strdup(var_value));
}

char	*handle_var_heredoc(char **buffer, char **env)
{
	char	*result;
	char	append[2];
	char	*var;

	env = env;
	result = ft_strdup("");
	while (**buffer)
	{
		if (**buffer == '$')
		{
			var = handle_var(buffer, env);
			if (!var || !ft_strcmp(var, ""))
				return (free(result), NULL);
			result = ft_strjoin_free(result, var);
			continue ;
		}
		else
		{
			append[0] = **buffer;
			append[1] = '\0';
			result = ft_strjoin_free(result, ft_strdup(append));
			(*buffer)++;
		}
	}
	return (result);
}
