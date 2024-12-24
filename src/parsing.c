/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:34:06 by sombru            #+#    #+#             */
/*   Updated: 2024/12/22 05:57:34 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command *create_command(char **args, t_atribute atribute)
{
	t_command *new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
		return (NULL);
	new_command->arguemnts = args;
	new_command->atribute = atribute;
	new_command->next = NULL;
	return (new_command);
}
void	add_command(t_command **commands, t_command *new_command)
{
	t_command *current;

	if (!new_command)
		return ;
	if (!*commands)
	{
		*commands = new_command;
		return ;
	}
	current = *commands;
	while (current->next)
		current = current->next;
	current->next = new_command;
}


t_command *parse_tokens(t_token *tokens)
{
	t_command 	*commands;
	char		**args;
	int			i;

	commands = NULL;
	while (tokens)
	{
		args = malloc((MAX_ENV_SIZE) * sizeof * args);
		i = 0;
		while (tokens && (tokens->type == TOKEN_STR || is_redirection_token(tokens->type)))
		{
			if (tokens->type == TOKEN_STDIN)
			{
				args[i] = ft_strdup(STDIN);
				i++;
				tokens = tokens->next;
			}
			if (tokens->type == TOKEN_STDOUT)
			{
				args[i] = ft_strdup(STDOUT);
				i++;
				tokens = tokens->next;
			}
			if (tokens->type == TOKEN_APPEND)
			{
				args[i] = ft_strdup(APPEND);
				i++;
				tokens = tokens->next;
			}
			if (tokens->type == TOKEN_HEREDOC)
			{
				args[i] = ft_strdup(HEREDOC);
				i++;
				tokens = tokens->next;
			}
			else
			{
				args[i] = ft_strdup(tokens->value);
				i++;
				tokens = tokens->next;
			}
		}
		if (tokens && tokens->type == TOKEN_CMDAND)
		{
			args[i] = NULL;
			add_command(&commands, create_command(args, CMDAND));
			tokens = tokens->next;
			continue;
		}
		if (tokens && tokens->type == TOKEN_CMDOR)
		{
			args[i] = NULL;
			add_command(&commands, create_command(args, CMDOR));
			tokens = tokens->next;
			continue;
		}
		if (tokens && tokens->type == TOKEN_PIPE)
		{
			args[i] = NULL;
			add_command(&commands, create_command(args, CHILD));
			tokens = tokens->next;
			continue;
		}
		args[i] = NULL;;
		add_command(&commands, create_command(args, PARENT));
		if (tokens)
			tokens = tokens->next;
	}

	return (commands);
}

void	free_commands(t_command *commands)
{
	t_command *current;
	t_command *next;

	current = commands;
	while (current)
	{
		next = current->next;
		free(current->arguemnts);
		free(current);
		current = next;
	}
}