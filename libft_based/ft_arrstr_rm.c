/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrstr_rm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:51:44 by pasha             #+#    #+#             */
/*   Updated: 2025/01/09 18:39:06 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Remove a string from an array and shift the rest of array accordingly
// returns NULL if no array or index is out of bounds
char	**ft_arrstr_rm(char **array, int index, int size)
{
	int		i;
	int		new_index;
	char	**new_array;

	if (!array || index < 0 || index >= size)
		return (NULL);
	new_array = malloc((size) * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	new_index = 0;
	while (i < size)
	{
		if (i == index)
		{
			i++;
			continue ;
		}
		new_array[new_index] = ft_strdup(array[i]);
		i++;
		new_index++;
	}
	new_array[new_index] = NULL;
	ft_free_array(array);
	return (new_array);
}
