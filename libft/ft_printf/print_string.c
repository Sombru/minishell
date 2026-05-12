/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:59:14 by sombru            #+#    #+#             */
/*   Updated: 2025/06/21 15:00:15 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*get_string(const char *arg)
{
	const char	*str;

	if (arg)
		str = arg;
	else
		str = "(null)";
	return (str);
}

int	print_string(t_format *f, const char *arg)
{
	int			count;
	int			len;
	int			out_len;
	const char	*str;

	str = get_string(arg);
	count = 0;
	if (!arg && f->dot)
		str = "";
	len = ft_strlen(str);
	out_len = len;
	if (f->dot && f->precision < out_len)
		out_len = f->precision;
	if (!f->minus && f->field_witdh)
		count += apply_format(f, out_len);
	if (out_len > 0)
		count += write(1, str, out_len);
	if (f->minus && f->field_witdh)
		count += apply_format(f, out_len);
	return (count);
}
