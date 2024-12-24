/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:00:01 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/23 08:20:41 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char	*ft_get_line(char *string)
{
	int		i;
	char	*str;

	i = 0;
	if (!string[i])
		return (NULL);
	while (string[i] && string[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (string[i] && string[i] != '\n')
	{
		str[i] = string[i];
		i++;
	}
	if (string[i] == '\n')
	{
		str[i] = string[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_string(char *string)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (string[i] && string[i] != '\n')
		i++;
	if (!string[i])
	{
		free(string);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(string) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (string[i])
		str[j++] = string[i++];
	str[j] = '\0';
	free(string);
	return (str);
}


char	*ft_read_to_string(int fd, char *string)
{
    char	*buff;
    char	*tmp;
    int		rd_bytes;

    if (!string)
    {
        string = (char *)malloc(1);
        string[0] = '\0';
    }
    buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buff)
        return (NULL);
    rd_bytes = 1;
    while (!ft_strchr(string, '\n') && rd_bytes != 0)
    {
        rd_bytes = read(fd, buff, BUFFER_SIZE);
        if (rd_bytes == -1)
            return (free(buff), NULL);
        buff[rd_bytes] = '\0';
        tmp = ft_strjoin(string, buff);
        free(string);
        string = tmp;
    }
    return (free(buff), string);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*string = NULL;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	string = ft_read_to_string(fd, string);
	if (!string)
		return (NULL);
	line = ft_get_line(string);
	string = ft_new_string(string);
	return (line);
}
// int main()
// {
// 	int fd;
// 	char *line;
// 	int i = 10;

// 	fd = open("test.txt", O_CREAT | O_RDONLY);
// 	while (i)
// 	{
// 		line = get_next_line(0);
// 		printf("%s", line);
// 		free(line);
// 		i--;
// 	}
// 	close(fd);
// 	return (0);
// }