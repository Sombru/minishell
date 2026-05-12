/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:19:51 by sombru            #+#    #+#             */
/*   Updated: 2025/06/21 15:24:44 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	debug_format(const t_format *f)
{
	printf("FORMAT:\nhash: %d\
		\nminus: %d\
		\nplus: %d\
		\nspace: %d\
		\nzero: %d\
		\ndot :%d\
		\ndefault_: %d\
		\nfield_witdh: %d\
		\nprecision: %d\
		\nspecifier: %c\
		\n",
		f->hash,
		f->minus,
		f->plus,
		f->space,
		f->zero,
		f->dot,
		f->default_,
		f->field_witdh,
		f->precision,
		f->specifier);
}
