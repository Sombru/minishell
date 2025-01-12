/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_gather_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:53:35 by pkostura          #+#    #+#             */
/*   Updated: 2025/01/12 12:21:04 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*handle_wildcard(char **input, char *word)
{
	char	*wildcard;
	char	tmp[2];

	wildcard = handle_wildcard_expansion(ft_strdup(word));
	if (!wildcard)
	{
		if (**input != '\0')
		{
			tmp[0] = **input;
			tmp[1] = '\0';
			word = ft_strjoin_free(word, ft_strdup(tmp));
			(*input)++;
		}
	}
	else
	{
		free(word);
		return (wildcard);
	}
	return (word);
}

static char	*handle_quotes(char **input, char **env, char *word,
		int *quotes_flag)
{
	char	*part;

	if (**input == '\'')
	{
		*quotes_flag = 1;
		part = handle_single_quotes(input);
		if (!part)
			return (free(word), NULL);
		word = ft_strjoin_free(word, part);
	}
	else if (**input == '"')
	{
		*quotes_flag = 1;
		part = handle_double_quotes(input, env);
		if (!part)
			return (free(word), NULL);
		word = ft_strjoin_free(word, part);
	}
	return (word);
}

static char	*handle_special_characters(char **input, char **env, char *word,
		int *quotes_flag)
{
	char	*var;

	word = handle_quotes(input, env, word, quotes_flag);
	if (!word)
		return (NULL);
	if (**input == '$')
	{
		var = handle_var(input, env);
		if (!var || !ft_strcmp(var, ""))
			return (free(word), NULL);
		word = ft_strjoin_free(word, var);
	}
	return (word);
}

char	*gather_word(char **input, char **env)
{
	char	*word;
	char	tmp[2];
	int		quotes_flag;

	word = ft_strdup("");
	quotes_flag = 0;
	while (**input && **input != '|' && **input != '>'
		&& **input != '<' && (**input != '&' || *(*input + 1) != '&'))
	{
		word = handle_special_characters(input, env, word, &quotes_flag);
		if (!word)
			return (NULL);
		if (**input && ft_isspace(**input))
			break ;
		if (**input && **input != '\'' && **input != '"' && **input != '$')
		{
			tmp[0] = **input;
			tmp[1] = '\0';
			word = ft_strjoin_free(word, ft_strdup(tmp));
			(*input)++;
		}
	}
	if (!quotes_flag && ft_strchr(word, '*'))
		word = handle_wildcard(input, word);
	return (word);
}
