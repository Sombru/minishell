/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:53:08 by nspalevi          #+#    #+#             */
/*   Updated: 2025/01/09 18:41:10 by pkostura         ###   ########.fr       */
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

bool	is_first_and_last_char(const char *str, char ch)
{
	size_t	len;

	if (!str || ft_strlen(str) <= 1)
		return (false);
	len = ft_strlen(str);
	return (str[0] == ch && str[len - 1] == ch);
}
