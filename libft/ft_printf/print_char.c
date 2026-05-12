/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:53:33 by sombru            #+#    #+#             */
/*   Updated: 2025/06/21 15:06:29 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(t_format *f, const int arg)
{
	int	count;

	count = 0;
	if (f->default_ && f->field_witdh)
		count += apply_format(f, 1);
	count += write(1, &arg, 1);
	if (f->field_witdh && f->minus)
		count += apply_format(f, 1);
	return (count);
}
