/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 04:46:08 by sombru            #+#    #+#             */
/*   Updated: 2024/12/24 19:46:12 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**reparse_args(char **args, int num_of_args)
{
	int	j;
	int i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], STDIN) == 0 || ft_strcmp(args[i], STDOUT) == 0
			|| ft_strcmp(args[i], APPEND) == 0 || ft_strcmp(args[i], HEREDOC) == 0)
		{
			j = i;
			args[j] = ft_strdup(args[num_of_args - 2]);
			args[j + 1] = ft_strdup(args[num_of_args - 1]);
			args[num_of_args - 2] = NULL;
		}
		i++;
	}
	return (args);
}

void	add_redirection(t_redirections **redirections, t_redirections *new_redirection)
{
	t_redirections	*current;

	if (!new_redirection)
		return ;
	if (!*redirections)
	{
		*redirections = new_redirection;
		return ;
	}
	current = *redirections;
	while (current->next)
		current = current->next;
	current->next = new_redirection;
}

t_redirections	*create_redirection(char *type, char *destination)
{
	t_redirections	*new_redirection;

	new_redirection = malloc(sizeof(t_redirections));
	if (!new_redirection)
		return (NULL);
	new_redirection->type = type;
	new_redirection->destination = destination;
	new_redirection->next = NULL;
	return (new_redirection);
}

t_redirections	*find_redirections(char **args)
{
	t_redirections	*redirections;
	char			*type;
	char			*destination;
	int				i;

	redirections = NULL;
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], STDIN) == 0
		|| ft_strcmp(args[i], STDOUT) == 0
		|| ft_strcmp(args[i], APPEND) == 0
		|| ft_strcmp(args[i], HEREDOC) == 0)
		{
			type = ft_strdup(args[i]);
			destination = ft_strdup(args[i + 1]);
			add_redirection(&redirections, create_redirection(type, destination));
			i++;
		}
		i++;
	}
	return (redirections);
	
}
void	free_redirections(t_redirections *redirections)
{
	t_redirections	*current;
	t_redirections	*next;

	current = redirections;
	while (current)
	{
		next = current->next;
		free(current->type);
		free(current->destination);
		free(current);
		current = next;
	}
}