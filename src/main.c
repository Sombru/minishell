#include "minishell.h"

int main()
{
	t_token* tokens;
	t_ast_node* ast;

	while (1)
	{
		char* input = readline("minishell> ");
		if (!input)
			return 0;
		add_history(input);
		tokens = tokenize(input);
		print_tokens(tokens);
		ast = parse(tokens);
	}
}