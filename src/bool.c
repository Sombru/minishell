/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:53:08 by nspalevi          #+#    #+#             */
/*   Updated: 2025/01/03 13:03:55 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_special_token(int token)
{
	if (token == TOKEN_PIPE || token == TOKEN_CMDAND || token == TOKEN_CMDOR)
		return (true);
	return (false);
}

bool	is_redirection_token(int token)
{
	if (token == TOKEN_STDIN || token == TOKEN_STDOUT || token == TOKEN_APPEND
		|| token == TOKEN_HEREDOC)
		return (true);
	return (false);
}

bool	is_output_redirection(t_redirections *redirections)
{
	while (redirections)
	{
		if (ft_strcmp(redirections->type, STDOUT) == 0)
			return (true);
		if (ft_strcmp(redirections->type, APPEND) == 0)
			return (true);
		redirections = redirections->next;
	}
	return (false);
}

bool	is_input_redirection(t_redirections *redirections)
{
	while (redirections)
	{
		if (ft_strcmp(redirections->type, STDIN) == 0)
			return (true);
		if (ft_strcmp(redirections->type, HEREDOC) == 0)
			return (true);
		redirections = redirections->next;
	}
	return (false);
}
