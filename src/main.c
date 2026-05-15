#include "minishell.h"

int main()
{
	t_token* tokens;

	while (1)
	{
		char* input = readline("minishell> ");
		if (!input)
			return 0;
		tokens = tokenize(input);
		print_tokens(tokens);	
	}
}