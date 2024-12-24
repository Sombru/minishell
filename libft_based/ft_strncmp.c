/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:33:37 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/07 15:43:15 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// function compares two n bytes of strings s1 and s2
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i ;

	i = 0;
	while ((*s1 != '\0' || *s2 != '\0') && i != n)
	{
		if (*s1 < *s2)
			return (*s1 - *s2);
		if (*s1 > *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
		i++;
	}
	return (0);
}
