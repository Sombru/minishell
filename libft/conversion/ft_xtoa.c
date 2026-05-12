/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:46:42 by sombru            #+#    #+#             */
/*   Updated: 2025/06/21 15:25:54 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_xlen(unsigned int x)
{
	int	i;

	i = 0;
	while (x)
	{
		x /= 16;
		++i;
	}
	return (i);
}

static const char	*get_hex_digits(int *upper)
{
	if (upper && *upper)
		return ("0123456789ABCDEF");
	else
		return ("0123456789abcdef");
}

// function converts x into hexadecimal string
// casing is specified by upper flag
char	*ft_xtoa(unsigned int x, int upper)
{
	char		*result;
	const char	*digits;
	int			len;

	if (!x)
		return (ft_strdup("0"));
	len = ft_xlen(x);
	result = malloc(sizeof(char) * (len + 1));
	digits = get_hex_digits(&upper);
	result[len] = '\0';
	while (len-- && x != 0)
	{
		result[len] = digits[x % 16];
		x /= 16;
	}
	return (result);
}
