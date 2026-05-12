/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:52:18 by sombru            #+#    #+#             */
/*   Updated: 2026/03/21 17:51:53 by pasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// malloc, free, write,
// va_start, va_arg, va_copy, va_end
inline static void	resolve_invalid_flags(t_format *f)
{
	if (f->zero && f->minus)
		f->zero = 0;
	if (f->dot && f->zero)
		f->zero = 0;
	if (f->minus && f->default_)
		f->default_ = 0;
	if (f->plus && f->space)
		f->space = 0;
}

inline static char	*get_format_string(const char *input)
{
	int	i;

	i = 0;
	while (!ft_strchr("cspdiuxX%", *input))
	{
		(input)++;
		i++;
	}
	return (ft_strndup(input - i, i + 1));
}

int	expand(const char *input, va_list arg)
{
	t_format	f;
	char		*format_string;

	if (*input == '%')
		return (write(1, "%", 1));
	format_string = get_format_string(input);
	f.default_ = 0;
	f.dot = 0;
	f.field_witdh = 0;
	f.hash = 0;
	f.minus = 0;
	f.plus = 0;
	f.precision = 0;
	f.space = 0;
	f.zero = 0;
	f.specifier = 'n';
	parse_flags(format_string, &f);
	resolve_invalid_flags(&f);
	parse_specifier(format_string, &f);
	free(format_string);
	return (convert(&f, arg));
}

int	ft_printf(const char *input, ...)
{
	int		count;
	va_list	arg;

	count = 0;
	va_start(arg, input);
	while (*input)
	{
		if (*input == '%')
		{
			count += expand(++input, arg);
			while (!ft_strchr("cspdiuxX%", *input))
				input++;
		}
		else
			count += write(STDOUT_FILENO, input, 1);
		input++;
	}
	va_end(arg);
	return (count);
}

// typedef struct s_int_case
// {
// 	const char	*name;
// 	const char	*format;
// 	int			value;
// }	t_int_case;

// typedef struct s_uint_case
// {
// 	const char	*name;
// 	const char	*format;
// 	unsigned int	value;
// }	t_uint_case;

// typedef struct s_str_case
// {
// 	const char	*name;
// 	const char	*format;
// 	const char	*value;
// }	t_str_case;

// static void	run_int_cases(const t_int_case *cases, size_t count)
// {
// 	size_t	i;
// 	int		my_ret;
// 	int		or_ret;

// 	i = 0;
// 	while (i < count)
// 	{
// 		printf("[int] %s | format: \"%s\" | value: %d\n", cases[i].name,
// 			cases[i].format, cases[i].value);
// 		fflush(stdout);
// 		my_ret = ft_printf("my: ");
// 		my_ret += ft_printf(cases[i].format, cases[i].value);
// 		my_ret += ft_printf("\n");
// 		or_ret = printf("or: ");
// 		or_ret += printf(cases[i].format, cases[i].value);
// 		or_ret += printf("\n");
// 		printf("ret -> my: %d | or: %d\n\n", my_ret, or_ret);
// 		i++;
// 	}
// }

// static void	run_uint_cases(const t_uint_case *cases, size_t count)
// {
// 	size_t	i;
// 	int		my_ret;
// 	int		or_ret;

// 	i = 0;
// 	while (i < count)
// 	{
// 		printf("[unsigned] %s | format: \"%s\" | value: %u\n", cases[i].name,
// 			cases[i].format, cases[i].value);
// 		fflush(stdout);
// 		my_ret = ft_printf("my: ");
// 		my_ret += ft_printf(cases[i].format, cases[i].value);
// 		my_ret += ft_printf("\n");
// 		or_ret = printf("or: ");
// 		or_ret += printf(cases[i].format, cases[i].value);
// 		or_ret += printf("\n");
// 		printf("ret -> my: %d | or: %d\n\n", my_ret, or_ret);
// 		i++;
// 	}
// }

// static void	run_str_cases(const t_str_case *cases, size_t count)
// {
// 	size_t	i;
// 	int		my_ret;
// 	int		or_ret;

// 	i = 0;
// 	while (i < count)
// 	{
// 		printf("[string] %s | format: \"%s\"\n", cases[i].name,
// 			cases[i].format);
// 		fflush(stdout);
// 		my_ret = ft_printf("my: ");
// 		my_ret += ft_printf(cases[i].format, cases[i].value);
// 		my_ret += ft_printf("\n");
// 		or_ret = printf("or: ");
// 		or_ret += printf(cases[i].format, cases[i].value);
// 		or_ret += printf("\n");
// 		printf("ret -> my: %d | or: %d\n\n", my_ret, or_ret);
// 		i++;
// 	}
// }

// int	main(void)
// {
// 	const t_int_case	int_cases[] = {
// 		{"space flag", " % 4d ", -20},
// 		{"plus flag", " %+4d ", -20},
// 		{"precision 2", " %.2d ", -2},
// 		{"precision 3", " %.3d ", -11},
// 		{"precision zero, zero value", " %.0d ", 0},
// 		{"width + precision", " %8.3d ", 42}
// 	};
// 	const t_uint_case	uint_cases[] = {
// 		{"hex precision 1", " %.1x ", 0},
// 		{"hex precision zero", " %.0x ", 0},
// 		{"hex width + precision", " %8.5x ", 42},
// 		{"unsigned precision", " %.4u ", 12}
// 	};
// 	const t_str_case	str_cases[] = {
// 		{"string precision", " %.3s ", "hello"},
// 		{"string width + precision", " %8.3s ", "hello"},
// 		{"null string precision", " %.3s ", NULL}
// 	};

// 	run_int_cases(int_cases, sizeof(int_cases) / sizeof(int_cases[0]));
// 	run_uint_cases(uint_cases, sizeof(uint_cases) / sizeof(uint_cases[0]));
// 	run_str_cases(str_cases, sizeof(str_cases) / sizeof(str_cases[0]));
// 	return (0);
// }