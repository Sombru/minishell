/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:05:03 by sombru            #+#    #+#             */
/*   Updated: 2025/01/14 15:20:53 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct s_piping
{
    int		cmd_count;
    int		*pipes;
    pid_t	*pids;
    int		*status;
}	t_piping;

static t_piping	*init_piping(t_command **commands)
{
    t_piping	*piping;
    int			i;

    piping = malloc(sizeof(t_piping));
    if (!piping)
        return (NULL);
    piping->cmd_count = 0;
    while (commands && (*commands)->atribute == CHILD)
    {
        piping->cmd_count++;
        *commands = (*commands)->next;
    }
    piping->cmd_count++;
    if (DEBUG_MODE)
        printf("Command count: %d\n", piping->cmd_count);
    piping->pipes = malloc(sizeof(int) * 2 * (piping->cmd_count - 1));
    piping->status = malloc(sizeof(int) * piping->cmd_count);
    piping->pids = malloc(sizeof(pid_t) * piping->cmd_count);
    i = 0;
    while (i < piping->cmd_count - 1)
    {
        pipe(piping->pipes + i * 2);
        i++;
    }
    return (piping);
}

int	pipe_commands(t_command **commands, char **env)
{
    t_command		*cmd_list;
    t_descriptor	*descriptor;
    t_piping		*piping;
    int				ret;
    int				i;
    int				j;

	cmd_list = *commands;
    piping = init_piping(commands);
    ret = SUCCESS;
    // cm list should point on the fist child in the sequence
	printf("cmd_list: %s\n", cmd_list->arguemnts[0]);
    i = 0;
    while (cmd_list && i < piping->cmd_count)
    {
        piping->pids[i] = fork();
        if (piping->pids[i] == 0)
        {
            if (handle_redirections(cmd_list, &descriptor, env) == SUCCESS)
            {
                if (i > 0)
                    dup2(piping->pipes[(i - 1) * 2], STDIN_FILENO);
                if (i < piping->cmd_count - 1)
                    dup2(piping->pipes[i * 2 + 1], STDOUT_FILENO);
                j = 0;
                while (j < 2 * (piping->cmd_count - 1))
                {
                    close(piping->pipes[j]);
                    j++;
                }
                execute_command(cmd_list->arguemnts, env, descriptor, cmd_list);
                ft_free_array(env);
                free_commands(cmd_list);
                free(piping->pipes);
                free(piping->pids);
                free(piping->status);
                free_descriptor(descriptor);
                exit(manage_exit_status(555));
            }
            else
            {
                ft_free_array(env);
                free_commands(cmd_list);
                free(piping->pipes);
                free(piping->pids);
                free(piping->status);
                free_descriptor(descriptor);
                exit(manage_exit_status(555));
            }
        }
        if (DEBUG_MODE)
            printf("Forked process with PID: %d\n", piping->pids[i]);
        cmd_list = cmd_list->next;
        i++;
    }
    i = 0;
    signal(SIGINT, handle_sigint_child);
    while (i < 2 * (piping->cmd_count - 1))
        close(piping->pipes[i++]);
    i = 0;
    while (i < piping->cmd_count)
    {
        waitpid(piping->pids[i], &piping->status[i], 0);
        if (WTERMSIG(piping->status[i]) != 0)
        {
            ret = manage_exit_status(WTERMSIG(piping->status[i]));
        }
        i++;
    }
    free(piping->pipes);
    free(piping->pids);
    free(piping->status);
    free(piping);
    *commands = cmd_list;
    return (manage_exit_status(ret));
}
