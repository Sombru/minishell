/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:24:11 by sombru            #+#    #+#             */
/*   Updated: 2026/03/21 17:51:04 by pasha            ###   ########.fr       */
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

char	*ft_itoa_printf(unsigned int n, int *out_nbr_len)
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

static char	resolve_digit_sign(t_format *f, int is_negative)
{
	if (is_negative)
		return ('-');
	if (f->plus)
		return ('+');
	if (f->space)
		return (' ');
	return ('\0');
}

static int	print_digit_formatted(t_format *f, char *result, t_digit *d)
{
	int	count;
	int	total_len;

	count = 0;
	total_len = d->len + d->precision_zeros + (d->sign != '\0');
	if (!f->minus && f->field_witdh)
	{
		if (f->zero && !f->dot && d->sign)
		{
			count += write(1, &d->sign, 1);
			d->sign = '\0';
		}
		count += apply_format(f, total_len);
	}
	if (d->sign)
		count += write(1, &d->sign, 1);
	while (d->precision_zeros-- > 0)
		count += write(1, "0", 1);
	count += write(1, result, d->len);
	if (f->minus && f->field_witdh)
		count += apply_format(f, total_len);
	return (count);
}

// Enough for -2147483648\0
int	print_digit(t_format *f, int arg)
{
	char	*result;
	t_digit	d;

	d.is_negative = 0;
	d.precision_zeros = 0;
	d.nbr = (long)arg;
	if (d.nbr < 0)
	{
		d.is_negative = 1;
		d.nbr = -d.nbr;
	}
	result = ft_itoa_printf((unsigned int)d.nbr, &d.len);
	d.sign = resolve_digit_sign(f, d.is_negative);
	if (f->dot && f->precision == 0 && d.nbr == 0)
		d.len = 0;
	if (f->dot && f->precision > d.len)
		d.precision_zeros = f->precision - d.len;
	d.len = print_digit_formatted(f, result, &d);
	free(result);
	return (d.len);
}
