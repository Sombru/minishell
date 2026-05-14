#include "minishell.h"

int main()
{
	// t_token* tokens;

	while (1)
	{
		char* input = readline(NULL);
		if (!input)
			return 0;
		free(input);
		// tokens = tokenize(input);
		// while(tokens)
		// {
			// ft_printf("tok: %s\n", tokens->value);
			// tokens = tokens->next;
		// }

	}
}