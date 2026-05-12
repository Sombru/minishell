/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:03:34 by sombru            #+#    #+#             */
/*   Updated: 2025/06/21 15:04:18 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	write_hex_prefix(int upper)
{
	if (upper)
		return (write(1, "0X", 2));
	return (write(1, "0x", 2));
}

static void	init_hex_data(t_format *f, unsigned int arg,
	char *hex, t_hex_data *d)
{
	d->len = (int)ft_strlen(hex);
	d->prefix_len = 0;
	d->prefix_printed = 0;
	d->precision_zeros = 0;
	if (f->dot && f->precision == 0 && arg == 0)
		d->len = 0;
	if (f->dot && f->precision > d->len)
		d->precision_zeros = f->precision - d->len;
	if (f->hash && arg)
		d->prefix_len = 2;
	d->total_len = d->len + d->precision_zeros + d->prefix_len;
}

static int	print_hex_content(t_format *f, int upper,
	char *hex, t_hex_data *d)
{
	int	count;

	count = 0;
	if (!f->minus && f->field_witdh)
	{
		if (f->zero && !f->dot && d->prefix_len)
		{
			count += write_hex_prefix(upper);
			d->prefix_printed = 1;
		}
		count += apply_format(f, d->total_len);
	}
	if (d->prefix_len && !d->prefix_printed)
		count += write_hex_prefix(upper);
	while (d->precision_zeros-- > 0)
		count += write(1, "0", 1);
	if (d->len > 0)
		count += write(1, hex, d->len);
	if (f->minus && f->field_witdh)
		count += apply_format(f, d->total_len);
	return (count);
}

int	print_hex(t_format *f, unsigned int arg, int upper)
{
	char		*hex;
	int			count;
	t_hex_data	d;

	hex = ft_xtoa(arg, upper);
	init_hex_data(f, arg, hex, &d);
	count = print_hex_content(f, upper, hex, &d);
	free(hex);
	return (count);
}
