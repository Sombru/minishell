/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:30:18 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/07 15:29:18 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// function checks if character is alphanumeric
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
