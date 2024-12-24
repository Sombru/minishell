/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 01:41:43 by sombru            #+#    #+#             */
/*   Updated: 2024/12/21 03:45:21 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *handle_var(char **input, char **env)
{
    char *var_name;
    char *var_value;
    int len;
    char *start;

    (*input)++;

	// Handle the special case for "$?"
    if (**input == '?')
    {
        (*input)++; 
        return (ft_itoa(manage_exit_status(555))); // Retrieve the current exit status
    }
    if (**input == '\0' || isspace(**input) || !ft_isalnum(**input))
        return (ft_strdup("$"));
    start = *input;
    while (**input && (ft_isalnum(**input) || **input == '_'))
        (*input)++;
    len = *input - start;
    var_name = strndup(start, len);
    if (!var_name || !ft_strcmp(var_name, ""))
        return (NULL);
    var_value = ft_getenv(var_name, env);
    free(var_name);
    if (!var_value)
        return (NULL);

    return (ft_strdup(var_value));
}

char *handle_var_heredoc(char **input, char **env)
{
    char *result = ft_strdup("");
    char *var_name;
    char *var_value;
    char *start;
    char *temp;
    int len;

    while (**input)
    {
        if (**input == '$')
        {
            (*input)++;
            // Handle the special case for "$?"
            if (**input == '?')
            {
                (*input)++;
                temp = ft_itoa(manage_exit_status(555)); // Retrieve the current exit status
                result = ft_strjoin_free(result, temp);
                free(temp);
                continue;
            }
            if (**input == '\0' || isspace(**input) || !ft_isalnum(**input))
            {
                result = ft_strjoin_free(result, ft_strdup("$"));
                continue;
            }
            start = *input;
            while (**input && (ft_isalnum(**input) || **input == '_'))
                (*input)++;
            len = *input - start;
            var_name = strndup(start, len);
            if (!var_name)
                return (NULL);
            var_value = ft_getenv(var_name, env);
            free(var_name);
            if (!var_value)
                var_value = "";
            result = ft_strjoin_free(result, ft_strdup(var_value));
        }
        else
        {
            temp = strndup(*input, 1);
            result = ft_strjoin_free(result, temp);
            (*input)++;
        }
    }
    return result;
}
