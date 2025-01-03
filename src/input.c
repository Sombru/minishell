/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:48:13 by nspalevi          #+#    #+#             */
/*   Updated: 2025/01/03 14:38:33 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*display_prompt(void)
{
	char	*input;
	char	*prompt;
	char	*exit_status;
	char	*colored_status;

	exit_status = ft_itoa(manage_exit_status(555));
	if (ft_strcmp(exit_status, "0") == 0)
		colored_status = ft_strjoin(G, exit_status);
	else
		colored_status = ft_strjoin(RED, exit_status);
	prompt = ft_strjoin(colored_status, C" minishell$> "RST);
	input = readline(prompt);
	free(prompt);
	free(exit_status);
	free(colored_status);
	if (input && *input)
		add_history(input);
	return (input);
}

int	is_valid_input(t_token *tokens)
{
	if (is_special_token(tokens->type))
	{
		printf(SYN_ERR " `%s'" RST "\n", tokens->value);
		return (FAILURE);
	}
	while (tokens)
	{
		if ((is_redirection_token(tokens->type)
				&& (!tokens->next || tokens->next->type != TOKEN_STR)))
		{
			printf(SYN_ERR " `%s'" RST "\n", tokens->value);
			return (FAILURE);
		}
		if ((is_special_token(tokens->type)
				&& (!tokens->next || (tokens->next->type != TOKEN_STR
						&& !is_redirection_token(tokens->next->type)))))
		{
			printf(SYN_ERR " `%s'" RST "\n", tokens->value);
			return (FAILURE);
		}
		tokens = tokens->next;
	}
	return (SUCCESS);

}
