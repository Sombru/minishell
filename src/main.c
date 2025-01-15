/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:24:39 by pkostura          #+#    #+#             */
/*   Updated: 2025/01/15 10:08:00 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_input_null(char *input, char **env)
{
	if (input == NULL)
	{
		printf("\n");
		free(input);
		ft_free_array(env);
		rl_clear_history();
		exit(manage_exit_status(555));
	}
}

static void	process_input(char *input, char **env)
{
	t_token		*tokens;
	t_command	*commands;

	tokens = ft_tokenize(input, env);
	if (tokens && is_valid_input(tokens))
	{
		free_tokens(tokens);
		free(input);
		manage_exit_status(1);
		return ;
	}
	commands = parse_tokens(tokens);
	if (tokens)
	{
		free_tokens(tokens);
		execution_protocol(commands, env);
		free_commands(commands);
		free(input);
	}
	else
		free(input);
}

static void	main_loop(char **env)
{
	char	*input;

	while (1)
	{
		unlink(HEREDOC_TMP);
		handle_signals();
		input = display_prompt();
		if (input == NULL)
			handle_input_null(input, env);
		process_input(input, env);
	}
}

int	main(int argc, char **argv, char **env_list)
{
	char	**env;

	(void)argc;
	(void)argv;
	env = store_environment(env_list);
	main_loop(env);
	return (0);
}
