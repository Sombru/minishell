/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:01:26 by sombru            #+#    #+#             */
/*   Updated: 2025/01/09 18:39:32 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// counts the number of arguments in a string array
int	ft_count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}
