#include "minishell.h"

static char* type_to_str(t_token* token)
{
	if (token->type == T_AND)
		return ("T_AND");
	if (token->type == T_OR)
		return ("T_OR");
	if (token->type == T_APPEND )
		return ("T_APPEND");
	if (token->type == T_HEREDOC)
		return ("T_HEREDOC");
	if (token->type == T_PIPE)
		return ("T_PIPE");
	if (token->type == T_LPAREN)
		return ("T_LPAREN");
	if (token->type == T_RPAREN)
		return ("T_RPAREN");
	if (token->type == T_REDIR_IN)
		return ("T_REDIR_IN");
	if (token->type == T_REDIR_OUT)
		return ("T_REDIR_OUT");
	return ("T_WORD");
}

void print_tokens(t_token* tokens)
{
	int i;

	i = 0;
	ft_printf("=======tokens======\n");
	if (!tokens)
		ft_printf("NONE");
	while (tokens)
	{
		ft_printf("%d. %s:%s\n", i, type_to_str(tokens), tokens->value);
		tokens = tokens->next;
		++i;
	}
	ft_printf("========end========\n");
}

static void	print_indent(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		ft_printf("    ");
		i++;
	}
}

static void	print_command_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
}

static const char	*get_node_name(t_node_type type)
{
	if (type == NODE_COMMAND)
		return ("COMMAND");
	if (type == NODE_AND)
		return ("AND");
	if (type == NODE_OR)
		return ("OR");
	if (type == NODE_PIPE)
		return ("PIPE");
	if (type == NODE_SUBSHELL)
		return ("SUBSHELL");
	return ("UNKNOWN");
}

static void	print_ast_recursive(t_ast_node *ast, int depth)
{
	if (!ast)
	{
		ft_printf("NONE");
		return ;
	}

	print_indent(depth);

	ft_printf("%s", get_node_name(ast->type));

	if (ast->type == NODE_COMMAND)
	{
		ft_printf(": ");
		print_command_args(ast->arguments);
	}

	ft_printf("\n");

	if (ast->left)
	{
		print_indent(depth);
		ft_printf("├── left\n");
		print_ast_recursive(ast->left, depth + 1);
	}

	if (ast->right)
	{
		print_indent(depth);
		ft_printf("└── right\n");
		print_ast_recursive(ast->right, depth + 1);
	}
}

void	print_ast(t_ast_node *ast)
{
	ft_printf("======= AST =======\n");
	print_ast_recursive(ast, 0);
	ft_printf("===================\n");
}