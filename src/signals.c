/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:02:42 by sombru            #+#    #+#             */
/*   Updated: 2025/01/29 13:16:07 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*sigint_prompt(void)
{
	char	*prompt;
	char	*exit_status;
	char	*colored_status;

	exit_status = ft_itoa(g_status(555));
	if (ft_strcmp(exit_status, "0") == 0)
		colored_status = ft_strjoin(G, exit_status);
	else
		colored_status = ft_strjoin(RED, exit_status);
	prompt = ft_strjoin(colored_status, C " minishell$> " RST);
	free(exit_status);
	free(colored_status);
	return (prompt);
}

void	handle_sigint(int sig)
{
	char	*tmp;

	(void)sig;
	if (matching_mode(2) == true)
	{
		matching_mode(0);
		write(STDOUT_FILENO, "\n", 1);
		rl_done = 1;
		tmp = sigint_prompt();
		write(STDERR_FILENO, tmp, ft_strlen(tmp));
		free(tmp);
		return ;
	}
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_parent(int sig)
{
	(void)sig;
	if (no_nl(2) == true)
	{
		g_status(130);
	}
	if (no_nl(2) == false)
		write(STDERR_FILENO, "\n", 1);
}

void	handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
