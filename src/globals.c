/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:32:54 by sombru            #+#    #+#             */
/*   Updated: 2025/01/29 10:31:06 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// flag: 127 on command not found
// flag: 0 on succes
// flag: 1 on error
// flag: 555 for current value
int	manage_exit_status(int set_flag)
{
	static int	exit_status = 0;

	if (set_flag == 555)
		return (exit_status);
	exit_status = set_flag;
	return (exit_status);
}

// flag: 1 for matching_mode
// flag: 0 to disable
// flag: 2 for current value
bool	matching_mode(int set_flag)
{
	static bool	matching_mode = 0;

	if (set_flag > 1)
		return (matching_mode);
	matching_mode = set_flag;
	return (matching_mode);
}

bool	no_nl(int set_flag)
{
	static bool	no_nl = 0;

	if (set_flag > 1)
		return (no_nl);
	no_nl = set_flag;
	return (no_nl);
}
