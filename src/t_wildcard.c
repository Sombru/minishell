/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_wildcard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 02:13:52 by sombru            #+#    #+#             */
/*   Updated: 2024/12/21 15:48:03 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**free_files_and_return_null(char **files, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(files[i]);
		i++;
	}
	free(files);
	return (NULL);
}

static int	match_pattern(const char *filename, const char *start, const char *end)
{
	size_t	start_len;
	size_t	end_len;
	size_t	filename_len;

	start_len = ft_strlen(start);
	end_len = ft_strlen(end);
	filename_len = ft_strlen(filename);
	if (filename_len < start_len + end_len)
		return (0);
	if (ft_strncmp(filename, start, start_len) != 0)
		return (0);
	if (ft_strcmp(filename + filename_len - end_len, end) != 0)
		return (0);
	return (1);
}


static char	**collect_files(DIR *dir, const char *start, const char *end)
{
	struct dirent	*entry;
	char			**files;
	int				count;

	files = NULL;
	count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.' && match_pattern(entry->d_name, start, end))
		{
			files = realloc(files, sizeof(char *) * (count + 2));
			if (!files)
				return (NULL);

			files[count] = ft_strdup(entry->d_name);
			if (!files[count])
				return (free_files_and_return_null(files, count));
			count++;
		}
		entry = readdir(dir);
	}
	if (files)
		files[count] = NULL;
	return (files);
}

static char	*get_directory_contents(char *start, char *end)
{
	DIR		*dir;
	char	**files;
	char	*result;

	if (!end)
		end = ft_strdup("");
	if (!start)
		start = ft_strdup("");
	dir = opendir(".");
	if (dir == NULL)
		return (NULL);

	files = collect_files(dir, start, end);
	closedir(dir);
	if (!files)
		return (NULL);
	result = ft_arrcomb(files, ' ');
	free(files);
	return (result);
}
char	*handle_wildcard_expansion(char *word)
{
	char	**pattern;
	char	*wildcard;
	char	*expanded;

	pattern = ft_split(word, '*');
	if (pattern[0] == NULL)
	{
		free(word);
		free(pattern);
		return (ft_stradd_start_end(get_directory_contents("", ""), '*'));
	}
	wildcard = word;
	wildcard = ft_strchr(wildcard, '*') + 1;
	if (!pattern[1] && *wildcard != '\0')
	{
		pattern[1] = pattern[0];
		pattern[0] = ft_strdup("");
	}
	expanded = get_directory_contents(pattern[0], pattern[1]);
	free(word);
	free(pattern);
	if (expanded == NULL)
		return (NULL);
	expanded = ft_stradd_start_end(expanded, '*');
	return (expanded);
}
