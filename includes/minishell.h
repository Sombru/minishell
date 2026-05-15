/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:59:18 by nspalevi          #+#    #+#             */
/*   Updated: 2025/01/29 13:16:07 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define RST "\033[0m"    // reset to default color
# define RED "\033[1;31m" // bold red
# define G "\033[1;32m"   // bold green
# define Y "\033[1;33m"   // bold Yellow
# define B "\033[1;34m"   // bold blue
# define M "\033[1;35m"   // bold magenta
# define C "\033[1;36m"   // bold cyan
# define W "\033[1;37m"   // bold white

typedef enum e_token_type
{
	T_WORD,
	T_AND, 
	T_OR,
	T_PIPE,
	T_LPAREN,
	T_RPAREN,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

typedef struct s_operator
{
	char			*symbol;
	t_token_type	type;
}	t_operator;

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
	t_token_type	type;
}	t_token;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}	t_node_type;

// debug

void print_tokens(t_token* tokens);

// tokenize

t_token* tokenize(const char* input);



#endif