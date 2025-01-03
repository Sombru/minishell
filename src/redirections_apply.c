/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 05:55:28 by sombru            #+#    #+#             */
/*   Updated: 2025/01/03 13:23:33 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	apply_redirections(t_redirections *redirections, char **env)
{
	t_redirections	*current;
	int				status;

	current = redirections;
	status = 0;
	while (current)
	{
		if (status == FAILURE)
			return (FAILURE);
		if (ft_strcmp(current->type, STDIN) == 0)
			status = input_redirection(current->destination);
		else if (ft_strcmp(current->type, STDOUT) == 0)
			status = output_redirection(current->destination);
		else if (ft_strcmp(current->type, APPEND) == 0)
			status = append_redirection(current->destination);
		else if (ft_strcmp(current->type, HEREDOC) == 0)
			status = heredoc_redirection(current->destination, env);
		current = current->next;
	}
	return (status);
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
		return (FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		manage_exit_status(1);
		return (FAILURE);
	}
	manage_exit_status(0);
	close(fd);
	return (SUCCESS);
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
		return (FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		manage_exit_status(1);
		return (FAILURE);
	}
	manage_exit_status(0);
	close(fd);
	return (SUCCESS);
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
		return (FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		manage_exit_status(1);
		return (FAILURE);
	}
	manage_exit_status(0);
	close(fd);
	return (SUCCESS);
}
extern int	g_matching_mode;

int	heredoc_redirection(char *delimiter, char **env)
{
	int		fd;
	char	*buffer;
	char	*expanded;
	char	*result;

	if (DEBUG_MODE)
		printf("DEBUG: heredoc redirection\n");
	fd = open(HEREDOC_TMP, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	g_matching_mode = 1;
	while (g_matching_mode != 0)
	{
		buffer = readline("heredoc> ");
		if (!buffer || !g_matching_mode)
			break ;
		if (ft_strcmp(buffer, delimiter) == 0)
		{
			free(buffer);
			break ;
		}
		result = buffer;
		expanded = handle_var_heredoc(&buffer, env);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
		free(result);
	}
	if (!g_matching_mode)
	{
		close(fd);
		unlink(HEREDOC_TMP);
		manage_exit_status(1);
		return (FAILURE);
	}
	manage_exit_status(0);
	close(fd);
	return (input_redirection(HEREDOC_TMP));
}
