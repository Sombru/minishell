/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcomb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:14:20 by sombru            #+#    #+#             */
/*   Updated: 2024/12/21 15:47:07 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	concat_strings(char *result, char **array, const char ch)
{
	int	i;
	char	separator[2];

	separator[0] = ch;
	separator[1] = '\0';
	i = 0;
	while (array[i])
	{
		ft_strcat(result, array[i]);
		if (array[i + 1])
			ft_strcat(result, separator);
		i++;
	}
}

// Combines all strings in the array into one string separated by the character ch
char	*ft_arrcomb(char **array, const char ch)
{
	size_t	total_length;
	int		i;
	char	*result;

	if (!array || !*array)
		return (ft_strdup(""));
	total_length = 0;
	i = 0;
	while (array[i])
	{
		total_length += ft_strlen(array[i]) + 1;
		i++;
	}
	result = malloc(total_length + 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	concat_strings(result, array, ch);
	return (result);
}
