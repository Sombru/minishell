/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:51:25 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/07 15:42:13 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// function appends the string src to the end of dest
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	dest_len;
	unsigned int	total_len;
	unsigned int	remaining_space;
	unsigned int	i;

	dest_len = ft_strlen(dest);
	if (dest_len > size)
		total_len = size + ft_strlen(src);
	else
		total_len = dest_len + ft_strlen(src);
	remaining_space = size - dest_len - 1;
	i = 0;
	if (size <= dest_len)
	{
		return (total_len);
	}
	while (src[i] != '\0' && i < remaining_space)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (total_len);
}
