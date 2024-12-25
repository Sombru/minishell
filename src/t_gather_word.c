/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_gather_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 01:33:07 by sombru            #+#    #+#             */
/*   Updated: 2024/12/25 17:07:36 by pasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *gather_word(char **input, char **env)
{
    char *word;
    char tmp[2];
    char *var;
	int  quotes_flag;
    char *wildcard;

	word = ft_strdup("");
	quotes_flag = 0;
    while (**input && !isspace(**input) && **input != '|' && **input != '>' && **input != '<' && (**input != '&' || *(*input + 1) != '&'))
    {
        if (**input == '\'')
        {
			quotes_flag = 1;
            char *part = handle_single_quotes(input);
            if (!part)
                return (free(word), NULL);
            word = ft_strjoin_free(word, part);
        }
        else if (**input == '"')
        {
			quotes_flag = 1;
            char *part = handle_double_quotes(input, env);
            if (!part)
                return (free(word), NULL);
            word = ft_strjoin_free(word, part);
        }
        else if (**input == '$')
        {
            var = handle_var(input, env);
            if (!var || !ft_strcmp(var, ""))
                return (free(word), NULL);
            word = ft_strjoin_free(word, var);
        }
        else
        {
            tmp[0] = **input;
            tmp[1] = '\0';
            word = ft_strjoin_free(word, ft_strdup(tmp));
            (*input)++;
        }
    }
	if (!quotes_flag && ft_strchr(word, '*'))
	{
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
    }
    return word;
}
