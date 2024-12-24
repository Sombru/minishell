/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 05:55:28 by sombru            #+#    #+#             */
/*   Updated: 2024/12/24 20:37:00 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	apply_redirections(t_redirections *redirections, char **env)
{
	t_redirections	*current;

	current = redirections;
	while (current)
	{
		if (ft_strcmp(current->type, STDIN) == 0)
			return (input_redirection(current->destination));
		else if (ft_strcmp(current->type, STDOUT) == 0)
			return (output_redirection(current->destination));
		else if (ft_strcmp(current->type, APPEND) == 0)
			return (append_redirection(current->destination));
		else if (ft_strcmp(current->type, HEREDOC) == 0)
			return (heredoc_redirection(current->destination, env));
		current = current->next;
	}
	return (0);
}

int	output_redirection(char *destination)
{
	int	fd;

	if (DEBUG_MODE)
		printf("DEBUG: output redirection\n");
	fd = open(destination, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("minishell");
		manage_exit_status(1);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		manage_exit_status(1);
		return (-1);
	}
	manage_exit_status(0);
	close(fd);
	return (0);
}

int	input_redirection(char *destination)
{
	int	fd;

	if (DEBUG_MODE)
		printf("DEBUG: input redirection\n");
	fd = open(destination, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		manage_exit_status(1);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		manage_exit_status(1);
		return (-1);
	}
	manage_exit_status(0);
	close(fd);
	return (0);
}

int	append_redirection(char *destination)
{
	int	fd;

	if (DEBUG_MODE)
		printf("DEBUG: append redirection\n");
	fd = open(destination, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("minishell");
		manage_exit_status(1);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		manage_exit_status(1);
		return (-1);
	}
	manage_exit_status(0);
	close(fd);
	return (0);
}
extern int	matching_mode;

int	heredoc_redirection(char *delimiter, char **env)
{
	int		fd;
	char	*buffer;

	if (DEBUG_MODE)
		printf("DEBUG: heredoc redirection\n");
	fd = open(HEREDOC_TMP, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	matching_mode = 1;
    while (matching_mode != 0)
    {
		printf("%d\n", matching_mode);
        buffer = readline("heredoc> ");
        if (!buffer || !matching_mode) // CTRL+D or read error
            break;
        if (ft_strcmp(buffer, delimiter) == 0)
        {
            free(buffer);
            break;
        }
        // Optionally expand variables here if you want
		env = env ;
        write(fd, buffer, ft_strlen(buffer));
        write(fd, "\n", 1);
        free(buffer);
    }
	if (!matching_mode)
	{
		close(fd);
		unlink(HEREDOC_TMP);
		manage_exit_status(1);
		return (-1);
	}
	manage_exit_status(0);
	close(fd);
	return (input_redirection(HEREDOC_TMP));
}
