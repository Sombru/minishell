/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:16:40 by sombru            #+#    #+#             */
/*   Updated: 2025/06/21 15:26:45 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	apply_format(t_format *f, int len_of_arg)
{
	int		count;
	char	pad;

	count = 0;
	pad = ' ';
	if (f->field_witdh <= len_of_arg)
		return (0);
	if (f->zero && !f->dot && !f->minus)
		pad = '0';
	f->field_witdh -= len_of_arg;
	while (f->field_witdh > 0)
	{
		count += (write(1, &pad, 1));
		f->field_witdh--;
	}
	return (count);
}

int	convert(t_format *f, va_list arg)
{
	if (f->specifier == 'c')
		return (print_char(f, va_arg(arg, int)));
	else if (f->specifier == 's')
		return (print_string(f, va_arg(arg, char *)));
	else if (f->specifier == 'p')
		return (print_pointer(f, va_arg(arg, void *)));
	else if (f->specifier == 'd' || f->specifier == 'i')
		return (print_digit(f, va_arg(arg, int)));
	else if (f->specifier == 'u')
		return (print_unsigned(f, va_arg(arg, unsigned int)));
	else if (f->specifier == 'x')
		return (print_hex(f, va_arg(arg, unsigned int), 0));
	else if (f->specifier == 'X')
		return (print_hex(f, va_arg(arg, unsigned int), 1));
	return (0);
}
