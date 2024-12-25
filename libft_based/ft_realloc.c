/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:33:41 by sombru            #+#    #+#             */
/*   Updated: 2024/12/25 22:36:23 by pasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Re-allocate the previously allocated block
// in PTR, making the new block SIZE bytes long.
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void	*new_ptr;
    size_t	copy_size;

    if (!ptr)
        return (malloc(new_size));
    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }
    new_ptr = malloc(new_size);
    if (!new_ptr)
        return (NULL);

    // Determine how many bytes to copy
    if (old_size < new_size)
        copy_size = old_size;
    else
        copy_size = new_size;

    ft_memcpy(new_ptr, ptr, copy_size);
    free(ptr);
    return (new_ptr);
}
