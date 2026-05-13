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

void print_table(t_token_table* map[TABLE_SIZE])
{
	int i = 0;
	ft_printf("Table\n");
	while (i < TABLE_SIZE)
	{
		if (!map[i])
			ft_printf("%d: ---------\n", i);
		else
			ft_printf("%d: %d\n", i, map[i]->value);
		++i;
	}
}

t_token_table** fill_table(t_token_table *map[TABLE_SIZE])
{
	int i = 0;
	while (i < TABLE_SIZE)
	{
		map[i] = 0;
		++i;
	}
	return map;
}

bool insert_to_table(t_token_table* map)
{
	if (!map)
		return false;
}

int hash(const char *key)
{
	static int hash_value = -1;
	(void)key;
	++hash_value;
	return hash_value;
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
	
	return NULL;
}