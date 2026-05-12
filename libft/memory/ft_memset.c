/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:07:58 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/29 15:09:15 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// function fills the first n bytes of the memory area pointed to by s 
// with the constant byte c
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n--)
	{
		*ptr++ = (unsigned char) c;
	}
	return (s);
}

// The  memset()  function  fills  the first n
// bytes of the memory area pointed  to  by  s
// with the constant byte c.