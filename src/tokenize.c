#include "minishell.h"

// static t_token add_token(const char* value, t_token_type type)
// {

// }

int	is_operator_char(char c)
{
	return (
		c == '&'
		|| c == '|'
		|| c == '<'
		|| c == '>'
		|| c == '('
		|| c == ')'
	);
}

t_token_type	get_operator_type(char *s)
{
	if (!ft_strncmp(s, "&&", 2))
		return (T_AND);
	if (!ft_strncmp(s, "||", 2))
		return (T_OR);
	if (!ft_strncmp(s, "<<", 2))
		return (T_HEREDOC);
	if (!ft_strncmp(s, ">>", 2))
		return (T_APPEND);
	if (!ft_strncmp(s, "|", 1))
		return (T_PIPE);
	if (!ft_strncmp(s, "(", 1))
		return (T_LPAREN);
	if (!ft_strncmp(s, ")", 1))
		return (T_RPAREN);
	if (!ft_strncmp(s, "<", 1))
		return (T_REDIR_IN);
	if (!ft_strncmp(s, ">", 1))
		return (T_REDIR_OUT);
	return (T_WORD);
}

t_token* tokenize(const char* input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			++i;
			continue ;
		}
		if (is_operator_char(input[i]))
		{
			
		}

	}
	
	return NULL;
}