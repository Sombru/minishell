/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:02:12 by sombru            #+#    #+#             */
/*   Updated: 2025/06/21 15:03:55 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_xlenl(unsigned long x)
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

static char	*ft_xtoal(unsigned long x, int upper)
{
	char		*result;
	const char	*digits;
	int			len;

	if (!x)
		return (ft_strdup("0"));
	len = ft_xlenl(x);
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

static int	print_hexl(t_format *f, unsigned long arg, int upper)
{
	char	*hex;
	int		count;
	int		len;

	count = 0;
	if (arg)
		hex = ft_xtoal(arg, upper);
	else
		hex = ft_strdup("(nil)");
	len = (int)ft_strlen(hex);
	if (f->hash && arg)
	{
		if (upper)
			count += write(1, "0X", 2);
		else
			count += write(1, "0x", 2);
		len += 2;
	}
	if (f->default_ && f->field_witdh)
		count += apply_format(f, len);
	count += write(1, hex, ft_strlen(hex));
	if (f->minus && f->field_witdh)
		count += apply_format(f, len);
	free(hex);
	return (count);
}

int	print_pointer(t_format *f, void *ptr)
{
	int	count;

	count = 0;
	f->hash = 1;
	count += print_hexl(f, (unsigned long)ptr, 0);
	return (count);
}
