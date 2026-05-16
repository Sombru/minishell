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