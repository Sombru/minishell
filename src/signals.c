/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:02:42 by sombru            #+#    #+#             */
/*   Updated: 2024/12/25 11:11:46 by pasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int matching_mode;

static char *sigint_promt(void)
{
	char	*prompt;
	char	*exit_status;
	char	*colored_status;

	exit_status = ft_itoa(manage_exit_status(555));
	if (ft_strcmp(exit_status, "0") == 0)
		colored_status = ft_strjoin(G, exit_status);
	else
		colored_status = ft_strjoin(RED, exit_status);
	prompt = ft_strjoin(colored_status, C" minishell$> "RST);
	free(exit_status);
	free(colored_status);
	return (prompt);
}

void	handle_sigint(int sig)
{
	(void)sig;
	char	*tmp;

	if (matching_mode)
	{
		matching_mode = 0;
		write(STDOUT_FILENO, "\n", 1);
		rl_done = 1; // Forces readline() to return NULL
		tmp = sigint_promt();
		write(STDERR_FILENO, tmp, ft_strlen(tmp));
		free(tmp);
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

