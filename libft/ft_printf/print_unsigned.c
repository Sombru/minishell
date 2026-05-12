/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:00:00 by sombru            #+#    #+#             */
/*   Updated: 2025/06/21 15:01:48 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nbrlen(unsigned int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 10;
		++i;
	}
	return (i);
}

char	*ft_uitoa_printf(unsigned int n, int *out_nbr_len)
{
	char	*str;
	int		len;

	if (!n)
	{
		*out_nbr_len = 1;
		return (ft_strdup("0"));
	}
	len = ft_nbrlen(n);
	*out_nbr_len = len;
	str = malloc(sizeof(*str) * (len + 1));
	str[len] = '\0';
	while (len-- && n != 0)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

// Enough for -2147483648\0
int	print_unsigned(t_format *f, unsigned int arg)
{
	char	*result;
	int		count;
	int		len;
	int		precision_zeros;
	int		total_len;

	count = 0;
	precision_zeros = 0;
	result = ft_uitoa_printf(arg, &len);
	if (f->dot && f->precision == 0 && arg == 0)
		len = 0;
	if (f->dot && f->precision > len)
		precision_zeros = f->precision - len;
	total_len = len + precision_zeros;
	if (!f->minus && f->field_witdh)
		count += apply_format(f, total_len);
	while (precision_zeros-- > 0)
		count += write(1, "0", 1);
	if (len > 0)
		count += write(1, result, len);
	if (f->minus && f->field_witdh)
		count += apply_format(f, total_len);
	free(result);
	return (count);
}
