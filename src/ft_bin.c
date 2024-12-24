/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 05:02:57 by sombru            #+#    #+#             */
/*   Updated: 2024/12/24 22:08:56 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *get_bin_path(char *command, char **env)
{
	int		i;
	char	*path;
	char	**path_split;

	i = 0;
	path = ft_getenv("PATH", env);
	path_split = ft_split(path, ':');
	while (path_split[i])
	{
		path = ft_strjoin(path_split[i], "/");
		path = ft_strjoin(path, command);
		if (access(path, F_OK) == 0)
		{
			free(path_split);
			return (path);
		}
		free(path);
		i++;
	}
	free(path_split);
	return (NULL);
}

int	execute_bin_command(char **args, char **env)
{
	char	*path;
	int		status;
	pid_t		pid;

	status = 0;
	if (is_bin_command(args[0]) == false)
		return (COMMAND_NOT_FOUND);
	if (args[0][0] == '/')
		path = ft_strdup(args[0]);
	else
		path = get_bin_path(args[0], env);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL); // Child uses default SIGINT
		status = execve(path, args, env);
		perror("execve");
		free(path);
		exit(FAILURE);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN); // Parent ignores SIGINT
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_sigint); // Restore parent handler
	}
	free(path);
	if (status != 0)
		return (FAILURE);
	return (SUCCESS);
}
