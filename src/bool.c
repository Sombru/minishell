/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:53:08 by nspalevi          #+#    #+#             */
/*   Updated: 2024/12/25 22:59:47 by pasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_special_token(int token)
{
	if (token == TOKEN_PIPE
		|| token == TOKEN_CMDAND 
		|| token == TOKEN_CMDOR)
		return (true);
	return (false);
}

bool	is_redirection_token(int token)
{
	if (token == TOKEN_STDIN 
		|| token == TOKEN_STDOUT 
		|| token == TOKEN_APPEND 
		|| token == TOKEN_HEREDOC)
		return (true);
	return (false);
}

bool	is_bin_command(char *command)
{
	static t_bin_cmd	bin_commands[] = {{"cat", "/bin/cat"},
	{"ls", "/bin/ls"}, {"grep", "/usr/bin/grep"},
	{"wc", "/usr/bin/wc"}, {"sort", "/usr/bin/sort"},
	{"head", "/usr/bin/head"}, {"tail", "/usr/bin/tail"},
	{"awk", "/usr/bin/awk"},
	{"sed", "/bin/sed"}, {"tr", "/usr/bin/tr"}, {NULL, NULL}};
	int					i;

	i = 0;
	while (bin_commands[i].name != NULL)
	{
		if (ft_strcmp(command, bin_commands[i].name) == 0
			|| ft_strcmp(command, bin_commands[i].path) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool  is_output_redirection(t_redirections *redirections)
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

bool is_input_redirection(t_redirections *redirections)
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
