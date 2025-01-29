/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:44:49 by sombru            #+#    #+#             */
/*   Updated: 2025/01/29 08:35:03 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*remove_first_and_last_char(char *str)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	if (len <= 2)
		return (ft_strdup(""));
	new_str = malloc(len - 1);
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, str + 1, len - 2);
	new_str[len - 2] = '\0';
	free(str);
	return (new_str);
}

static void	handle_pipe_and_logical_operators(char **input, t_token **tokens)
{
	if (**input == '|')
	{
		if (*(*input + 1) == '|')
		{
			add_token(tokens, create_token(TOKEN_CMDOR, "||"));
			*input += 2;
		}
		else
		{
			add_token(tokens, create_token(TOKEN_PIPE, "|"));
			(*input)++;
		}
	}
	else if (**input == ';')
	{
		add_token(tokens, create_token(TOKEN_CMDAND, ";"));
		(*input)++;
	}
	else if (**input == '&' && *(*input + 1) == '&')
	{
		add_token(tokens, create_token(TOKEN_CMDAND, "&&"));
		*input += 2;
	}
}

static void	handle_redirections_operators(char **input, t_token **tokens)
{
	if (**input == '>' && *(*input + 1) == '>')
	{
		add_token(tokens, create_token(TOKEN_APPEND, ">>"));
		*input += 2;
	}
	else if (**input == '>')
	{
		add_token(tokens, create_token(TOKEN_STDOUT, ">"));
		(*input)++;
	}
	if (**input == '<' && *(*input + 1) == '<')
	{
		add_token(tokens, create_token(TOKEN_HEREDOC, "<<"));
		*input += 2;
	}
	else if (**input == '<')
	{
		add_token(tokens, create_token(TOKEN_STDIN, "<"));
		(*input)++;
	}
}

static void	handle_word(char **input, char **env, t_token **tokens)
{
	char	*str;
	char	**expanded;
	int		i;

	str = gather_word(input, env);
	if (str && ft_strcmp(str, ""))
	{
		if (is_first_and_last_char(str, 31))
		{
			str = remove_first_and_last_char(str);
			expanded = ft_split(str, ' ');
			i = 0;
			while (expanded[i] != NULL)
			{
				add_token(tokens, create_token(TOKEN_STR, expanded[i]));
				i++;
			}
			ft_free_array(expanded);
		}
		else
			add_token(tokens, create_token(TOKEN_STR, str));
		free(str);
	}
	else
		free(str);
}

t_token	*ft_tokenize(char *input, char **env)
{
	t_token	*tokens;

	tokens = NULL;
	while (*input)
	{
		if (ft_isspace(*input))
			input++;
		else if (*input == '|' || (*input == '&' && *(input + 1) == '&') || *input == ';')
			handle_pipe_and_logical_operators(&input, &tokens);
		else if (*input == '>' || *input == '<')
			handle_redirections_operators(&input, &tokens);
		else
			handle_word(&input, env, &tokens);
	}
	return (tokens);
}
