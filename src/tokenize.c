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

t_token_type	get_operator_type(char *s, int *len)
{
	int	i;

	i = 0;
	while (g_operators[i].symbol)
	{
		*len = strlen(g_operators[i].symbol);

		if (ft_strncmp(s, g_operators[i].symbol, *len) == 0)
			return (g_operators[i].type);

		i++;
	}

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

	}
	

}