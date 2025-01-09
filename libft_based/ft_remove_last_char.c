/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_last_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:00:29 by pkostura          #+#    #+#             */
/*   Updated: 2025/01/09 11:53:00 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// removes last occurance of char ch from the string
char	*ft_remove_last_char(char *str, char ch)
{
	char	*last_occurrence;
	char	*result ;
	size_t	length;
	size_t	prefix_length;

	if (!str)
		return (NULL);
	last_occurrence = ft_strrchr(str, ch);
	if (!last_occurrence)
		return (ft_strdup(str));
	length = ft_strlen(str);
	result = malloc(length + 1);
	if (!result)
		return (NULL);
	prefix_length = last_occurrence - str;
	ft_strncpy(result, str, prefix_length);
	ft_strcpy(result + prefix_length, last_occurrence + 1);
	free(str);
	return (result);
}
