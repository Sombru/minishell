/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:55:01 by pkostura          #+#    #+#             */
/*   Updated: 2023/09/14 16:00:38 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n)
	{
		n /= 10;
		++i;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_nbrlen(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		if (n == INT_MIN)
		{
			str[--len] = '8';
			n /= 10;
		}
		n = -n;
	}
	while (len-- && n != 0)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

// The ft_nbrlen function is a static helper function that calculates the
// length (number of digits) of an integer. It takes an integer n as an
// argument and returns an integer representing the length. It uses a variable
// i to keep track of the length and a while loop to continuously divide the
// integer n by 10 until it becomes zero. This loop counts the number of
// iterations, which corresponds to the number of digits in the integer.
// It also accounts for negative numbers and returns a length of 1 for 
// zero or negative integers. This is useful for determining the length
//  of the resulting string.

// The ft_itoa function takes an integer n as input and begins by calculating
// its length using the ft_nbrlen helper function. It stores this length in 
// the len variable.

// The code then allocates memory for a character array (string) of size
// len + 1 using the ft_calloc function. The +1 is for the null-terminator
// ('\0') that marks the end of the string. If the allocation fails
// (i.e., str is NULL), the function returns NULL to indicate an error.

// The code handles special cases:

// If n is zero, it sets str[0] to '0' because the integer
// representation of zero is simply "0".
// If n is negative, it sets str[0] to '-'
// to represent the negative sign and then
// negates n to work with its absolute value.
// The code enters a loop to convert the integer
// n into a character string representation:

// It starts from the end of the str array and iterates
// backward (from len - 1 to 0).
// In each iteration, it calculates the last digit of n by
// taking the remainder when divided by 10 (n % 10) and converts
// it to a character by adding '0'. This digit is stored in str[len].
// It then divides n by 10 to remove the last digit.
// The loop continues until n becomes zero or until len reaches -1.
// Finally, the function returns the dynamically allocated character
// array str, which now contains the string representation of the integer.
