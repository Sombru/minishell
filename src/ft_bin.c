/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 05:02:57 by sombru            #+#    #+#             */
/*   Updated: 2024/12/25 22:00:34 by pasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_bin_path(char *command, char **env)
{
    char **path_split;
    char *tmp;
    char *ret_path;
    int i;

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
