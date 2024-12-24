/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:02:42 by sombru            #+#    #+#             */
/*   Updated: 2024/12/24 17:47:51 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int matching_mode;

void	handle_sigint(int sig)
{
	(void)sig;

	if (matching_mode)
	{
		matching_mode = 0;
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_done = 1; // Forces readline() to return NULL
		// unlink(HEREDOC_TMP);
		return ;
	}
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// Ctrl-\ does nothing
void	handle_sigquit(int sig)
{
	(void)sig;
}

void	handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

