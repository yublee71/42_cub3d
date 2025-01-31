/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:24:09 by yublee            #+#    #+#             */
/*   Updated: 2024/06/26 23:20:16 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_store_until_newline(char *stored)
{
	char	*temp;
	size_t	i;

	i = ft_chr_idx(stored, '\n');
	temp = stored;
	stored = ft_gnl_substr(stored, i, ft_strlen(stored));
	free(temp);
	return (stored);
}

void	*ft_free(char **s1, char *s2)
{
	free(*s1);
	free(s2);
	*s1 = NULL;
	return (NULL);
}

char	*ft_initialize(char *stored, int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stored)
	{
		stored = ft_strdup("");
		if (!stored)
			return (NULL);
	}
	return (stored);
}

size_t	ft_chr_idx(char *s, char c)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stored[FDMAX];
	char		*line;
	char		*buffer;
	ssize_t		rd_size;

	if (fd < 0)
		return (NULL);
	stored[fd] = ft_initialize(stored[fd], fd);
	line = ft_gnl_substr(stored[fd], 0, ft_chr_idx(stored[fd], '\n'));
	if (ft_chr_idx(stored[fd], '\n'))
		stored[fd] = ft_store_until_newline(stored[fd]);
	else if (stored[fd])
	{
		buffer = ft_malloc(BUFFER_SIZE + 1);
		rd_size = read(fd, buffer, BUFFER_SIZE);
		if (rd_size < 0)
			return (ft_free(&stored[fd], buffer));
		stored[fd] = ft_f_strjoin(stored[fd], buffer);
		if (rd_size > 0)
			return (get_next_line(fd));
		if (*stored[fd])
			line = ft_strdup(stored[fd]);
		stored[fd] = ft_free(&stored[fd], buffer);
	}
	return (line);
}
