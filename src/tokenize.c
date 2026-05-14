#include "minishell.h"

static t_token* add_token(const char* value, t_token_type type)
{

}

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

int	get_operator_length(t_token_type type)
{
	if (type == T_AND || type == T_OR)
		return (2);
	if (type == T_APPEND || type == T_HEREDOC)
		return (2);
	if (type == T_PIPE)
		return (1);
	if (type == T_LPAREN || type == T_RPAREN)
		return (1);
	if (type == T_REDIR_IN || type == T_REDIR_OUT)
		return (1);
	return (0);
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
	t_token* tokens = malloc(sizeof(t_token));
	while (*input)
	{
		if (ft_isspace(*input))
		{
			++input;
			continue ;
		}
		if (is_operator_char(*input))
		{
			tokens = add_token()
		}
	}
	
	return NULL;
}