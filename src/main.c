#include "minishell.h"

int main()
{
	t_shell shell;

	while (1)
	{
		char* input = readline("minishell> ");
		if (!input)
			return 0;
		add_history(input);
		tokenize(input, &shell);
		// print_tokens(shell.tokens);
		parse(&shell);
		print_ast(shell.ast);
	}
}