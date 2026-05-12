/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_smart.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:12:44 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/24 08:45:42 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_only_whitespace(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

// returns a line from a file excluding empty lines and trims '\n' ending char
char	*gnl_smart(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	while (line)
	{
		if (!is_only_whitespace(line))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	return (ft_rmlast_char(line, '\n'));
}
