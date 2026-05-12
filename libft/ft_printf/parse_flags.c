/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:23:42 by sombru            #+#    #+#             */
/*   Updated: 2025/06/21 15:07:27 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//  %[argument$][flags][width][.precision][length modifier]conversion
// '#+- 0'
static void	parse_field_width(char **format_string, t_format *f)
{
	f->field_witdh = ft_atoi(*format_string);
	f->default_ = 1;
	while (ft_isdigit(**format_string))
		(*format_string)++;
}

static void	parse_precision(char **format_string, t_format *f)
{
	f->dot = 1;
	(*format_string)++;
	f->precision = 0;
	if (ft_isdigit(**format_string))
	{
		f->precision = ft_atoi(*format_string);
		while (ft_isdigit(**format_string))
			(*format_string)++;
	}
}

void	parse_flags(char *format_string, t_format *f)
{
	while (format_string && *format_string
		&& ft_strchr("# +-0", *format_string))
	{
		if (*format_string == '#')
			f->hash = 1;
		else if (*format_string == '+')
			f->plus = 1;
		else if (*format_string == ' ')
			f->space = 1;
		else if (*format_string == '-')
			f->minus = 1;
		else if (*format_string == '0')
			f->zero = 1;
		format_string++;
	}
	if (*format_string && ft_isdigit(*format_string))
		parse_field_width(&format_string, f);
	if (*format_string == '.')
		parse_precision(&format_string, f);
}

int	parse_width(char **format_string, t_format *f)
{
	if (ft_isdigit((**format_string)))
		f->field_witdh = ft_atoi(*format_string);
	else
		f->field_witdh = ft_atoi(++(*format_string));
	while (ft_isdigit(**format_string))
		(*format_string)++;
	return (1);
}

void	parse_specifier(const char *format_string, t_format *f)
{
	while (*format_string != 0)
	{
		format_string++;
	}
	format_string--;
	f->specifier = *format_string;
}
