#include <minishell.h>

char	*gather_word(char *input)
{
	int 	i;

	i = 0;
	while (input[i] && !ft_isspace(input[i]) && !is_operator_char(input[i]))
	{
		++i;
	}
	return ft_strndup(input, i);
}