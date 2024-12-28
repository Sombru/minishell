/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:44:49 by sombru            #+#    #+#             */
/*   Updated: 2024/12/28 09:16:25 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool is_first_and_last_char(const char *str, char ch)
{
    if (!str || ft_strlen(str) <= 1)
        return false;

    size_t len = ft_strlen(str);
    return (str[0] == ch && str[len - 1] == ch);
}

static char *remove_first_and_last_char(char *str)
{
    size_t	len;
	char	*new_str;

	len = ft_strlen(str);
    if (len <= 2)
        return (ft_strdup(""));
    new_str = malloc(len - 1);
    if (!new_str)
        return NULL;
    ft_strncpy(new_str, str + 1, len - 2);
    new_str[len - 2] = '\0';
	free(str);
    return new_str;
}

t_token	*ft_tokenize(char *input, char **env)
{
	t_token	*tokens;
	char	*str;
	char 	**expanded;
	int		i;

	tokens = NULL;
	while (*input)
	{
		if (isspace(*input))
			input++;
		if (*input == '|')
		{
			if (*(input + 1) == '|')
			{
				add_token(&tokens, create_token(TOKEN_CMDOR, "||"));
				input += 2;
			}
			else
			{
				add_token(&tokens, create_token(TOKEN_PIPE, "|"));
				input++;
			}
		}
		if (*input == '&' && *(input + 1) == '&')
		{
			add_token(&tokens, create_token(TOKEN_CMDAND, "&&"));
			input += 2;
		}
		if (*input == '>')
		{
			if (*(input + 1) == '>')
			{
				add_token(&tokens, create_token(TOKEN_APPEND, ">>"));
				input += 2;
			}
			else
			{
				add_token(&tokens, create_token(TOKEN_STDOUT, ">"));
				input++;
			}
		}
		if (*input == '<')
		{
			if (*(input + 1) == '<')
			{
				add_token(&tokens, create_token(TOKEN_HEREDOC, "<<"));
				input += 2;
			}
			else
			{
				add_token(&tokens, create_token(TOKEN_STDIN, "<"));
				input++;
			}
		}
		else
		{
			str = gather_word(&input, env);
			if (str && ft_strcmp(str, ""))
			{
				if (is_first_and_last_char(str, 31))
				{
					str = remove_first_and_last_char(str);
					expanded = ft_split(str, ' ');
					i = 0;
					while (expanded[i] != NULL)
					{
						add_token(&tokens, create_token(TOKEN_STR, expanded[i]));
						i++;
					}
					ft_free_array(expanded);
				}
				else
					add_token(&tokens, create_token(TOKEN_STR, str));
				free(str);
			}
			else
				free(str);
		}		
		
	}
	return (tokens);
}
