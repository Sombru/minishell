#include <minishell.h>

static void syntax_error()
{
	ft_printf("bad_syntax\n");
	exit(1);
}

static t_node_type get_node_type(t_token_type type)
{
	if (type == T_AND)
		return (NODE_AND);
	if (type == T_OR)
		return (NODE_OR);
	if (type == T_PIPE)
		return (NODE_PIPE);
	// if (type == T_LPAREN)
		// return (NODE_SUBSHELL);
	// if (type == T_RPAREN)
		// return ("T_RPAREN");
	return (-1);
}

static t_ast_node* add_node(t_node_type type, char** args)
{
	t_ast_node* new_node;

	new_node = malloc(sizeof(t_ast_node));

	new_node->arguments = args;
	new_node->type = type;
	new_node->right = NULL;
	new_node->left = NULL;
	return new_node;
}

static t_ast_node	*parse_command(t_token **current, int token_count)
{
	char	**args;
	int		arg_count;

	args = malloc(sizeof(char *) * (token_count + 1));
	if (!args)
		return (NULL);

	arg_count = 0;
	while ((*current) && (*current)->type == T_WORD)
	{
		args[arg_count] = ft_strdup((*current)->value);
		arg_count++;
		*current = (*current)->next;
	}

	args[arg_count] = NULL;

	return (add_node(NODE_COMMAND, args));
}

// t_ast_node	*parse_expression(t_token **current)
// {
// 	return (parse_logical(current));
// }

t_ast_node	*parse_primary(t_token **current, int token_count)
{
	t_ast_node	*node;

	if ((*current) && (*current)->type == T_LPAREN)
	{
		*current = (*current)->next;

		node = parse_logical(current, token_count);

		if ((*current) && (*current)->type != T_RPAREN)
			(syntax_error());

		*current = (*current)->next;

		return (node);
	}

	return (parse_command(current, token_count));
}

t_ast_node	*parse_logical(t_token **current, int token_count)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*node;
	t_node_type	op;

	left = parse_primary(current, token_count);

	while ((*current)
		&& ((*current)->type == T_AND
		|| (*current)->type == T_OR))
	{
		op = get_node_type((*current)->type);
		*current = (*current)->next;

		right = parse_primary(current, token_count);

		node = add_node(op, NULL);
		node->left = left;
		node->right = right;

		left = node;
	}

	return (left);
}

void parse(t_shell* shell)
{
	shell->ast = parse_logical(&shell->tokens, shell->token_count);
}