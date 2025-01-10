/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:44:10 by nspalevi          #+#    #+#             */
/*   Updated: 2025/01/10 13:45:35 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_descriptor	*get_descriptors(void)
{
	t_descriptor	*descriptor;
	int				original_fds[2];
	int				prev_fd;

	descriptor = malloc(sizeof(t_descriptor));
	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
	prev_fd = dup(STDIN_FILENO);
	descriptor->original_fds[0] = original_fds[0];
	descriptor->original_fds[1] = original_fds[1];
	descriptor->prev_fd = prev_fd;
	return (descriptor);
}

int	count_children(t_command *commands)
{
	t_command	*current;
	int			count;

	count = 0;
	current = commands;
	while (current)
	{
		if (current->atribute == CHILD)
			count++;
		current = current->next;
	}
	return (count);
}

int	stdin_required(char *command)
{
	const char	*stdin_commands[] = {"cat", "grep", "awk", "wc", "sort",
		"sleep", NULL};
	int			i;

	i = 0;
	while (stdin_commands[i])
	{
		if (ft_strcmp(command, stdin_commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
