/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 01:34:37 by sombru            #+#    #+#             */
/*   Updated: 2025/01/29 06:30:06 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_single_quotes(char **input)
{
	char	*start;
	char	*piping;
	char	*temp;

	(*input)++;
	start = *input;
	piping = NULL;
	while (**input && **input != '\'')
		(*input)++;
	if (**input == '\'')
	{
		temp = ft_strndup(start, *input - start);
		piping = ft_strjoin_free(piping, temp);
		(*input)++;
		return (piping);
	}
	else
		return (handle_unmatched_single_quotes(start));
}

char	*handle_unmatched_single_quotes(char *start)
{
	char	*buffer;
	char	*nl;
	char	*piping;

	piping = ft_strdup(start);
	nl = ft_strdup("\n");
	matching_mode(true);
	while (matching_mode(2) == true)
	{
		buffer = readline("quote> ");
		if (!buffer || matching_mode(2) == false)
			return (free(piping), free(nl), NULL);
		piping = ft_strjoin_free(piping, nl);
		piping = ft_strjoin_free(piping, buffer);
		if (ft_strchr(piping, '\''))
		{
			piping = ft_remove_last_char(piping, '\'');
			break ;
		}
		nl = ft_strdup("\n");
	}
	return (piping);
}

char	*handle_double_quotes(char **input, char **env)
{
	char	*start;
	char	*piping;

	(*input)++;
	start = *input;
	piping = NULL;
	while (**input && **input != '"')
	{
		if (**input == '$')
		{
			piping = ft_strjoin_free(piping, ft_strndup(start, *input - start));
			piping = handle_double_quotes_var(input, env, piping);
			start = *input;
		}
		else
			(*input)++;
	}
	if (**input == '"')
	{
		piping = ft_strjoin_free(piping, ft_strndup(start, *input - start));
		(*input)++;
		return (piping);
	}
	else
		return (handle_unmatched_double_quotes(start, env));
}

char	*handle_double_quotes_var(char **input, char **env, char *piping)
{
	char	*var_value;

	var_value = handle_var(input, env);
	if (var_value)
		piping = ft_strjoin_free(piping, var_value);
	return (piping);
}

char	*handle_unmatched_double_quotes(char *start, char **env)
{
	char	*buffer;
	char	*nl;
	char	*piping;

	piping = ft_strdup(start);
	nl = ft_strdup("\n");
	matching_mode(true);
	while (matching_mode(2) == true)
	{
		buffer = readline("dquote> ");
		if (!buffer || matching_mode(2) == false)
			return (free(piping), free(nl), NULL);
		piping = ft_strjoin_free(piping, nl);
		piping = ft_strjoin_free(piping, buffer);
		piping = handle_var_heredoc(&piping, env);
		if (ft_strchr(piping, '"'))
		{
			piping = ft_remove_last_char(piping, '"');
			break ;
		}
		nl = ft_strdup("\n");
	}
	return (piping);
}
