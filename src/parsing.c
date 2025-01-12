/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:34:06 by sombru            #+#    #+#             */
/*   Updated: 2025/01/12 12:22:58 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_command_type(t_token *tokens)
{
	if (!tokens)
		return (PARENT);
	if (tokens->type == TOKEN_CMDAND)
		return (CMDAND);
	if (tokens->type == TOKEN_CMDOR)
		return (CMDOR);
	if (tokens->type == TOKEN_PIPE)
		return (CHILD);
	return (PARENT);
}

static void	parse_command_args(t_token *tokens, char **args, int i)
{
	if (tokens->type == TOKEN_STDIN)
		args[i] = ft_strdup(STDIN);
	else if (tokens->type == TOKEN_STDOUT)
		args[i] = ft_strdup(STDOUT);
	else if (tokens->type == TOKEN_APPEND)
		args[i] = ft_strdup(APPEND);
	else if (tokens->type == TOKEN_HEREDOC)
		args[i] = ft_strdup(HEREDOC);
	else
		args[i] = ft_strdup(tokens->value);
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*commands;
	char		**args;
	int			i;

	commands = NULL;
	while (tokens)
	{
		args = malloc((count_tokens(tokens) + 1) * sizeof * args);
		i = 0;
		while (tokens && (tokens->type == TOKEN_STR
				|| is_redirection_token(tokens->type)))
		{
			parse_command_args(tokens, args, i);
			tokens = tokens->next;
			i++;
		}
		args[i] = NULL;
		add_command(&commands, create_command(args, get_command_type(tokens)));
		if (tokens)
			tokens = tokens->next;
	}
	return (commands);
}
