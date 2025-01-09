/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:10:46 by sombru            #+#    #+#             */
/*   Updated: 2025/01/09 18:42:00 by pkostura         ###   ########.fr       */
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
}

void	free_commands(t_command *commands)
{
	t_command	*current;
	t_command	*next;
	int			i;

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
