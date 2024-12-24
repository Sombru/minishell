/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:07:58 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/07 15:37:27 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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