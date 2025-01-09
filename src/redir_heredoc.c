/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:44:07 by pkostura          #+#    #+#             */
/*   Updated: 2025/01/09 15:44:21 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_matching_mode;

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
	g_matching_mode = 1;
	while (g_matching_mode)
	{
		buffer = readline("heredoc> ");
		if (!g_matching_mode || !buffer)
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
