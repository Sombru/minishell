/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:11:09 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/18 22:20:00 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// function to join strings s1 and s2 to new string and free old strings
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (new_str);
}
