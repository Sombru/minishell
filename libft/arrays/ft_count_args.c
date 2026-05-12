/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:41:57 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/20 08:45:28 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// counts strints in char array
int	ft_count_args(char	**arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
	{
		i++;
	}
	return (i);
}
