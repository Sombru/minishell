/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 01:34:37 by sombru            #+#    #+#             */
/*   Updated: 2024/12/24 15:56:02 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int matching_mode;

char *handle_single_quotes(char **input)
{
	char 	*start;
	char 	*res;
	char 	*buffer;
	char	*temp;

	(*input)++;
	start = *input;
	res = ft_strdup("");
	while (**input && **input != '\'')
		(*input)++;
	if (**input == '\'')
	{
		// Append the remaining part
		temp = strndup(start, *input - start);
		res = ft_strjoin(res, temp);
		free(temp);
		(*input)++;	  // Move past the closing quote
		return (res); // Return the string
	}
	else
	{
		matching_mode = 1;
		printf("quote> ");
		buffer = ft_strjoin(start, readline(""));
		while (buffer && matching_mode)
		{
			res = ft_strjoin(res, "\n");
			res = ft_strjoin(res, buffer);
			if (ft_strchr(buffer, '\''))
			{
				res = ft_remove_last_char(res, '\'');
				break;
			}				
			printf("quote> ");
			buffer = readline("");
		}
		if (!buffer || !matching_mode)
		{
			free(res);
			return (NULL);
		}
	}
	return (res);
}

char *handle_double_quotes(char **input, char **env)
{
	char *start;
	char *res;
	char *temp;
	char *var_value;
	char *buffer;

	(*input)++;
	start = *input;
	res = strdup("");
	while (**input && **input != '"')
	{
		if (**input == '$')
		{
			// Append the part before the variable
			temp = strndup(start, *input - start);
			res = ft_strjoin(res, temp);
			free(temp);
			// Handle the variable
			var_value = handle_var(input, env);
			if (var_value)
			{
				res = ft_strjoin(res, var_value);
				free(var_value);
			}
			start = *input; // Update start to the new position
		}
		else
		{
			(*input)++;
		}
	}
	if (**input == '"')
	{
		// Append the remaining part
		temp = strndup(start, *input - start);
		res = ft_strjoin(res, temp);
		free(temp);
		(*input)++;	  // Move past the closing quote
		return (res); // Return the string
	}
	
	else
	{
		matching_mode = 1;
		printf("dquote> ");
		buffer = ft_strjoin(start, readline(""));
		while (buffer && matching_mode)
		{
	
			res = ft_strjoin(res, "\n");
			res = ft_strjoin(res, buffer);
			if (ft_strchr(buffer, '"'))
			{
				res = ft_remove_last_char(res, '"');
				break;
			}
			
			printf("dquote> ");
			buffer = readline("");
		}
		if (!buffer || !matching_mode)
		{
			free(res);
			return (NULL);
		}
	}
	return (res);
}