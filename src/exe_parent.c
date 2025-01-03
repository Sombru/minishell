/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_parent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:00:22 by sombru            #+#    #+#             */
/*   Updated: 2025/01/03 13:10:06 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_parent(t_descriptor *descriptor)
{
	close(descriptor->pipefd[1]);
	close(descriptor->prev_fd);
	descriptor->prev_fd = descriptor->pipefd[0];
	dup2(descriptor->original_fds[0], STDIN_FILENO);
	dup2(descriptor->original_fds[1], STDOUT_FILENO);
	return (SUCCESS);
}
