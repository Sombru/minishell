/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:44:07 by pkostura          #+#    #+#             */
/*   Updated: 2025/01/13 14:47:01 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static int	terminate_heredoc(int fd, char *buffer)
{
	close(fd);
	unlink(HEREDOC_TMP);
	free(buffer);
	manage_exit_status(1);
	return (FAILURE);
}

int	heredoc_redirection(char *delimiter, char **env)
{
	int		fd;
	char	*buffer;
	char	*nl;

	fd = open(HEREDOC_TMP, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	matching_mode(true);
	while (matching_mode(2) == true)
	{
		buffer = readline("heredoc> ");
		if (!buffer || matching_mode(2) == false)
			return (terminate_heredoc(fd, buffer));
		if (ft_strcmp(buffer, delimiter) == 0)
		{
			free(buffer);
			break ;
		}
		nl = ft_strdup("\n");
		buffer = handle_var_heredoc(&buffer, env);
		buffer = ft_strjoin_free(buffer, nl);
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	manage_exit_status(0);
	close(fd);
	return (input_redirection(HEREDOC_TMP));
}
