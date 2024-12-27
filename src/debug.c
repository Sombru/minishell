/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:49:38 by nspalevi          #+#    #+#             */
/*   Updated: 2024/12/27 11:04:32 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_args(char **args)
{
	int	i;

	i = 0;
	printf("DEBUG: Arguments:\n");
	while (args[i])
	{
		printf("Arg[%d]: `%s'\n", i, args[i]);
		i++;
	}
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token Type: %d, Value: %s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

void	print_commands(t_command *commands)
{

	while (commands)
	{
		print_args(commands->arguemnts);
		printf("Command atribute is:");
			if (commands->atribute == PARENT)
				printf(" PARENT\n");
			else if (commands->atribute == CHILD)
				printf(" CHILD\n");
			else if (commands->atribute == CMDOR)
				printf(" CMDOR\n");
			else if (commands->atribute == CMDAND)
				printf(" CMDAND\n");
		commands = commands->next;
	}
}