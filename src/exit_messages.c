/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_messages.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 07:05:06 by sombru            #+#    #+#             */
/*   Updated: 2025/01/29 10:32:28 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	command_not_found(char **args)
{
	char	*tmp;

	ft_putstr_fd(RED "minishell:" RST " command not found: " RED "`",
		STDERR_FILENO);
	tmp = ft_strjoin(args[0], "'\n" RST);
	ft_putstr_fd(tmp, STDERR_FILENO);
	free(tmp);
	return (COMMAND_NOT_FOUND);
}

int	no_file_error(char **args)
{
	char	*tmp;

	ft_putstr_fd(RED "minishell:" RST " No such file or directory: " RED "`",
		STDERR_FILENO);
	tmp = ft_strjoin(args[0], "'\n" RST);
	ft_putstr_fd(tmp, STDERR_FILENO);
	free(tmp);
	return (NO_FILE_ERROR);
}

int	seg_fault(void)
{
	ft_putstr_fd("Segmentation fault (core dumped)\n", STDERR_FILENO);
	return (SEG_FAULT);
}
