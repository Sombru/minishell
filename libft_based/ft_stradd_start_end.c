/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd_start_end.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:02:25 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/19 00:11:14 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// adds char ch at the start and ad the end of a string
char	*ft_stradd_start_end(char *str, char ch)
{
	size_t	len;
	char	*modified_str;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	modified_str = malloc(len + 3);
	if (!modified_str)
		return (NULL);
	modified_str[0] = ch;
	ft_strcpy(modified_str + 1, str);
	modified_str[len + 1] = ch;
	modified_str[len + 2] = '\0';
	free(str);
	return (modified_str);
}
