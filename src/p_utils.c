/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:10:46 by sombru            #+#    #+#             */
/*   Updated: 2025/01/12 18:32:37 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*create_command(char **args, t_atribute atribute)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
		return (NULL);
	new_command->arguemnts = args;
	new_command->atribute = atribute;
	new_command->next = NULL;
	new_command->prev = NULL;
	return (new_command);
}

void	add_command(t_command **commands, t_command *new_command)
{
	t_command	*current;

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
	new_command->prev = current;
}

void	free_commands(t_command *commands)
{
	t_command	*current;
	t_command	*next;
	int			i;

	while (commands && commands->prev)
		commands = commands->prev;
	current = commands;
	while (current)
	{
		i = 0;
		while (current->arguemnts[i])
		{
			free(current->arguemnts[i]);
			i++;
		}
		free(current->arguemnts);
		next = current->next;
		free(current);
		current = next;
	}
}
