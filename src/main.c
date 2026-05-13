#include "minishell.h"

int main()
{
	// t_token* tokens;

	printf("&&: %d\n", hash("&&"));
	printf("||: %d\n", hash("||"));
	printf(">>: %d\n", hash(">>"));
	printf(">: %d\n", hash(">"));
	printf("<: %d\n", hash("<"));
	printf("<<: %d\n", hash("<<"));
	printf("|: %d\n", hash("|"));
	printf("(: %d\n", hash("("));
	printf("): %d\n", hash(")"));
	t_token_table* map[TABLE_SIZE];
	fill_table(map);
	print_table(map);
	while (1)
	{
		char* input = readline(NULL);
		free(input);
		// tokens = tokenize(input);
		// while(tokens)
		// {
			// ft_printf("tok: %s\n", tokens->value);
			// tokens = tokens->next;
		// }

	}
}