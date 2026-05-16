#include <minishell.h>

// char** parse_args()

t_ast_node* add_node(t_ast_node** ast, t_node_type type)
{

}

t_ast_node* parse(t_token* tokens)
{
	t_ast_node* ast;
	int arg_count;
	char** args;

	ast = NULL;
	arg_count = 0;
	while (tokens)
	{
		if (tokens->type == T_WORD)
		{
			args[arg_count] = tokens->value;
			++arg_count;
		}
		tokens = tokens->next;
	}
	
	parse_expression();
	parse_logical();
	parse_primary();
}