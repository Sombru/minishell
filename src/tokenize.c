/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:44:49 by sombru            #+#    #+#             */
/*   Updated: 2024/12/25 22:12:21 by pasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// creates a new token with specific type and value
t_token	*create_token(t_token_var type, char *value)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type; // sets the type of the token
	new_token->value = ft_strdup(value);
	// duplicates the value of the token to avoid memory leaks
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token *current;

	if (!new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

static bool is_first_and_last_char(const char *str, char ch)
{
    if (!str || ft_strlen(str) <= 1)
        return false;

    size_t len = ft_strlen(str);
    return (str[0] == ch && str[len - 1] == ch);
}

static char *remove_first_and_last_char(char *str)
{
    size_t len = strlen(str);

    // If the string is too short to remove first and last characters, return an empty string
    if (len <= 2)
        return strdup("");

    // Allocate memory for the new string
    char *new_str = malloc(len - 1); // len - 2 for the characters + 1 for the null terminator
    if (!new_str)
        return NULL;

    // Copy the substring excluding the first and last characters
    strncpy(new_str, str + 1, len - 2);
    new_str[len - 2] = '\0'; // Null-terminate the new string

	free((char *)str);
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

void	free_tokens(t_token *tokens)
{
	t_token *temp;

	while (tokens)
	{
		temp = tokens;
		if (tokens->value)
			free(tokens->value);
		tokens = tokens->next;
		free(temp);
	}
}