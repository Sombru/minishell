/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:07:29 by pasha             #+#    #+#             */
/*   Updated: 2024/12/25 21:59:49 by pasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Frees the array of strings and all its elements
void	ft_free_array(char **arr)
{
    int i;

    i = 0;
    while (arr && arr[i])
        free(arr[i++]);
    free(arr);
}
