/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 05:02:57 by sombru            #+#    #+#             */
/*   Updated: 2025/01/12 21:53:01 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	command_not_found(char **args)
{
	char	*tmp;

	ft_putstr_fd(RED "minishell:" RST " command not found: " RED "`",
		STDERR_FILENO);
	tmp = ft_strjoin(args[0], "'\n" RST);
	ft_putstr_fd(tmp, STDERR_FILENO);
	free(tmp);
	return (COMMAND_NOT_FOUND);
}

char	*get_bin_path(char *command, char **env)
{
	char	**path_split;
	char	*tmp;
	char	*ret_path;
	int		i;

	if (ft_getenv("PATH", env) == NULL)
		return (NULL);
	path_split = ft_split(ft_getenv("PATH", env), ':');
	i = 0;
	while (path_split[i])
	{
		tmp = ft_strjoin(path_split[i], "/");
		ret_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(ret_path, F_OK) == 0)
		{
			ft_free_array(path_split);
			return (ret_path);
		}
		free(ret_path);
		i++;
	}
	ft_free_array(path_split);
	return (NULL);
}

int	execute_bin_command(char **args, char **env)
{
	char	*path;
	int		status;
	pid_t	pid;

	status = 0;
	if (args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/'))
		path = ft_strdup(args[0]);
	else
		path = get_bin_path(args[0], env);
	if (path == NULL)
		return (command_not_found(args));
	pid = fork();
	if (pid == 0)
		status = execve(path, args, env);
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, WNOHANG);
	}
	free(path);
	if (status != 0)
		return (FAILURE);
	return (SUCCESS);
}
