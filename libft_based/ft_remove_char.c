/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:55:42 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/07 16:46:15 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// function to remove all occurances of char s in string str
char	*ft_remove_char(const char *str, char s)
{
	int		len;
	char	*trimmed_str;
	int		i;
	int		j;

	len = strlen(str);
	trimmed_str = malloc(len + 1);
	if (!trimmed_str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] != s)
		{
			trimmed_str[j] = str[i];
			j++;
		}
		i++;
	}
	trimmed_str[j] = '\0';
	return (trimmed_str);
}
