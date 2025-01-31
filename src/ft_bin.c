/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 05:02:57 by sombru            #+#    #+#             */
/*   Updated: 2025/01/29 10:30:35 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exit_execve(pid_t pid, char **args)
{
	int	status;

	signal(SIGINT, handle_sigint_parent);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGSEGV)
			return (seg_fault());
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 126)
			return (no_file_error(args));
		return (WEXITSTATUS(status));
	}
	return (status);
}

char	*get_bin_path(char *command, char **env)
{
	char	**path_split;
	char	*tmp;
	char	*ret_path;
	int		i;

	if (ft_getenv("PATH", env) == NULL)
		return (free(command), NULL);
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
			return (free(command), ret_path);
		}
		free(ret_path);
		i++;
	}
	ft_free_array(path_split);
	return (free(command), NULL);
}

int	execute_bin_command(char **args, char **env, t_descriptor *descriptor,
		t_command *commands)
{
	static char	*exit_args[] = {"exit", "126", NULL};
	char		*path;
	pid_t		pid;

	if (args[0][0] == '/' || args[0][0] == '.' || args[0][1] == '/')
		path = ft_strdup(args[0]);
	else
		path = get_bin_path(ft_strdup(args[0]), env);
	if (path == NULL)
		return (command_not_found(args));
	pid = fork();
	if (pid == 0)
	{
		execve(path, args, env);
		free(path);
		ft_exit(exit_args, env, descriptor, commands);
	}
	free(path);
	return (exit_execve(pid, args));
}
