/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:08:05 by sombru            #+#    #+#             */
/*   Updated: 2026/03/21 17:51:24 by pasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include "../libft.h"

typedef struct s_format
{
	int		hash;
	int		minus;
	int		plus;
	int		dot;
	int		space;
	int		zero;
	int		default_;
	int		field_witdh;
	int		precision;
	char	specifier;
}	t_format;

typedef struct s_digit
{
	char	sign;
	int		len;
	int		is_negative;
	int		precision_zeros;
	long	nbr;
}	t_digit;

typedef struct s_hex_data
{
	int	len;
	int	prefix_len;
	int	prefix_printed;
	int	precision_zeros;
	int	total_len;
}	t_hex_data;

int		convert(t_format *f, va_list arg);
int		expand(const char *input, va_list arg);
void	parse_flags(char *format_string, t_format *f);
int		parse_width(char **format_string, t_format *f);
void	parse_specifier(const char *format_string, t_format *f);

void	debug_format(const t_format *f);

int		apply_format(t_format *f, int len_of_arg);

int		print_char(t_format *f, const int arg);
int		print_string(t_format *f, const char *arg);
int		print_pointer(t_format *f, void *ptr);
int		print_digit(t_format *f, int arg);
int		print_unsigned(t_format *f, unsigned int arg);
int		print_hex(t_format *f, unsigned int arg, int upper);

int		ft_printf(const char *input, ...);

#endif