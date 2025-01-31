/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:44:10 by nspalevi          #+#    #+#             */
/*   Updated: 2025/01/13 20:38:37 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_descriptor	*get_descriptors(void)
{
	t_descriptor	*descriptor;
	int				original_fds[2];

	descriptor = malloc(sizeof(t_descriptor));
	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
	descriptor->original_fds[0] = original_fds[0];
	descriptor->original_fds[1] = original_fds[1];
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
