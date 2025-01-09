/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 01:34:37 by sombru            #+#    #+#             */
/*   Updated: 2025/01/09 19:17:23 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_matching_mode;

char	*handle_single_quotes(char **input)
{
	char	*start;
	char	*res;
	char	*temp;

	(*input)++;
	start = *input;
	res = NULL;
	while (**input && **input != '\'')
		(*input)++;
	if (**input == '\'')
	{
		temp = ft_strndup(start, *input - start);
		res = ft_strjoin_free(res, temp);
		(*input)++;
		return (res);
	}
	else
		return (handle_unmatched_single_quotes(start));
}

char	*handle_unmatched_single_quotes(char *start)
{
	char	*buffer;
	char	*nl;
	char	*res;

	res = ft_strdup(start);
	nl = ft_strdup("\n");
	g_matching_mode = 1;
	while (g_matching_mode)
	{
		buffer = readline("quote> ");
		if (!buffer || !g_matching_mode)
			return (free(res), free(nl), NULL);
		res = ft_strjoin_free(res, nl);
		res = ft_strjoin_free(res, buffer);
		if (ft_strchr(res, '\''))
		{
			res = ft_remove_last_char(res, '\'');
			break ;
		}
		nl = ft_strdup("\n");
	}
	return (res);
}

char	*handle_double_quotes(char **input, char **env)
{
	char	*start;
	char	*res;

	(*input)++;
	start = *input;
	res = NULL;
	while (**input && **input != '"')
	{
		if (**input == '$')
		{
			res = ft_strjoin_free(res, ft_strndup(start, *input - start));
			res = handle_double_quotes_var(input, env, res);
			start = *input;
		}
		else
			(*input)++;
	}
	if (**input == '"')
	{
		res = ft_strjoin_free(res, ft_strndup(start, *input - start));
		(*input)++;
		return (res);
	}
	else
		return (handle_unmatched_double_quotes(start, env));
}

char	*handle_double_quotes_var(char **input, char **env, char *res)
{
	char	*var_value;

	var_value = handle_var(input, env);
	if (var_value)
		res = ft_strjoin_free(res, var_value);
	return (res);
}

char	*handle_unmatched_double_quotes(char *start, char **env)
{
	char	*buffer;
	char	*nl;
	char	*res;

	res = ft_strdup(start);
	nl = ft_strdup("\n");
	g_matching_mode = 1;
	while (g_matching_mode)
	{
		buffer = readline("dquote> ");
		if (!buffer || !g_matching_mode)
			return (free(res), free(nl), NULL);
		res = ft_strjoin_free(res, nl);
		res = ft_strjoin_free(res, buffer);
		res = handle_var_heredoc(&res, env);
		if (ft_strchr(res, '"'))
		{
			res = ft_remove_last_char(res, '"');
			break ;
		}
		nl = ft_strdup("\n");
	}
	return (res);
}
