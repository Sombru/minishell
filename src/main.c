/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:34:40 by nspalevi          #+#    #+#             */
/*   Updated: 2025/01/03 14:38:55 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// flag: 127 on command not found
// flag: 0 on no error
// flag: 1 on error
// flag: 555 for current value
int	manage_exit_status(int set_flag)
{
	static int	g_exit_status = 0;

	if (set_flag == 127)
	{
		g_exit_status = 127;
		return (g_exit_status);
	}
	if (set_flag == 0)
	{
		g_exit_status = 0;
		return (g_exit_status);
	}
	if (set_flag >= 1 && set_flag < 300)
	{
		if (g_exit_status == 127)
			g_exit_status = 1;
		else
			g_exit_status++;
		return (g_exit_status);
	}
	return (g_exit_status);
}

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

int			g_matching_mode = 0;

int	main(int argc, char **argv, char **env_list)
{
	char		*input;
	char		**env;
	t_token		*tokens;
	t_command	*commands;

	(void)argc;
	(void)argv;
	env = store_environment(env_list);
	while (1)
	{
		unlink(HEREDOC_TMP);
		handle_signals();
		input = display_prompt();
		if (input == NULL)
			handle_input_null(input, env);
		tokens = ft_tokenize(input, env);
		if (tokens && is_valid_input(tokens))
		{
			free_tokens(tokens);
			free(input);
			manage_exit_status(1);
			continue ;
		}
		commands = parse_tokens(tokens);
		if (tokens)
		{
			free_tokens(tokens);
			execution_protocol(commands, env, get_descriptors());
			free_commands(commands);
			free(input);
		}
		else
			free(input);
	}
	return (0);
}
