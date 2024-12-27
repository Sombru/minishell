/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:53:27 by sombru            #+#    #+#             */
/*   Updated: 2024/12/27 14:54:22 by sombru           ###   ########.fr       */
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
	new_token->type = type;
	new_token->value = ft_strdup(value);
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
