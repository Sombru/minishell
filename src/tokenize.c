#include "minishell.h"

int	is_operator_char(char c)
{
	return (
		c == '&'
		|| c == '|'
		|| c == '<'
		|| c == '>'
		|| c == '('
		|| c == ')'
	);
}

static int	get_operator_length(t_token_type type)
{
	if (type == T_AND || type == T_OR)
		return (2);
	if (type == T_APPEND || type == T_HEREDOC)
		return (2);
	if (type == T_PIPE)
		return (1);
	if (type == T_LPAREN || type == T_RPAREN)
		return (1);
	if (type == T_REDIR_IN || type == T_REDIR_OUT)
		return (1);
	return (0);
}

static t_token_type	get_operator_type(const char *s)
{
	if (!ft_strncmp(s, "&&", 2))
		return (T_AND);
	if (!ft_strncmp(s, "||", 2))
		return (T_OR);
	if (!ft_strncmp(s, "<<", 2))
		return (T_HEREDOC);
	if (!ft_strncmp(s, ">>", 2))
		return (T_APPEND);
	if (!ft_strncmp(s, "|", 1))
		return (T_PIPE);
	if (!ft_strncmp(s, "(", 1))
		return (T_LPAREN);
	if (!ft_strncmp(s, ")", 1))
		return (T_RPAREN);
	if (!ft_strncmp(s, "<", 1))
		return (T_REDIR_IN);
	if (!ft_strncmp(s, ">", 1))
		return (T_REDIR_OUT);
	return (T_WORD);
}


static void add_oprator_token(t_token** tokens, char** input)
{
	t_token* new_token = malloc(sizeof(t_token));
	t_token* current;
	t_token_type type;
	char* value;

	type = get_operator_type(*input);
	value = ft_strndup(*input, get_operator_length(type));
	*input += ft_strlen(value);
	new_token->next = NULL;
	new_token->type = type;
	new_token->value = value;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

static void add_word_token(t_token** tokens, char** input)
{
	t_token* new_token = malloc(sizeof(t_token));
	t_token* current;
	t_token_type type;
	char* value;

	type = T_WORD;
	value = gather_word(*input);
	*input += ft_strlen(value);
	new_token->next = NULL;
	new_token->type = type;
	new_token->value = value;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

t_token* tokenize(char* input)
{
	t_token* tokens;

	tokens = NULL;
	while (*input)
	{
		if (ft_isspace(*input))
			++input;
		if (is_operator_char(*input))
		{
			add_oprator_token(&tokens, &input);
			continue ;
		}
		else
		{
			add_word_token(&tokens, &input);
			continue ;
		}
		++input;
	}
	
	return tokens;
}