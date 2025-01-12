/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:44:10 by nspalevi          #+#    #+#             */
/*   Updated: 2025/01/12 15:39:16 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_descriptor	*get_descriptors(void)
{
	t_descriptor	*descriptor;
	int				original_fds[2];
	// int				prev_fd;

	descriptor = malloc(sizeof(t_descriptor));
	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
	// prev_fd = dup(STDIN_FILENO);
	descriptor->original_fds[0] = original_fds[0];
	descriptor->original_fds[1] = original_fds[1];
	// descriptor->prev_fd = prev_fd;
	return (descriptor);
}

void	free_descriptor(t_descriptor *descriptor)
{
	dup2(descriptor->original_fds[0], STDIN_FILENO);
	dup2(descriptor->original_fds[1], STDOUT_FILENO);
	close(descriptor->original_fds[0]);
	close(descriptor->original_fds[1]);
	free(descriptor);
}
