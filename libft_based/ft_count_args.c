/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:01:26 by sombru            #+#    #+#             */
/*   Updated: 2025/01/03 14:01:46 by sombru           ###   ########.fr       */
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
