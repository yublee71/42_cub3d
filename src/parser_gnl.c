/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:40:32 by mayeung           #+#    #+#             */
/*   Updated: 2025/05/06 16:42:31 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*ft_gnlstrchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	if (!c)
		return (str + i);
	return (NULL);
}

static char	*ft_gnlstrjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
		i++;
	j = 0;
	while (s2 && s2[j])
		j++;
	res = malloc(sizeof(char) * (i + j + 1));
	if (!res)
		return (NULL);
	i = -1 * (s1 != NULL);
	while (s1 && s1[++i])
		res[i] = s1[i];
	j = -1 * (s2 != NULL);
	while (s2 && s2[++j])
		res[i + j] = s2[j];
	res[i + j] = 0;
	return (res);
}

static char	*ft_gnlstrlcpy(char *src, char *dst, size_t size)
{
	size_t	i;

	i = 0;
	while (dst && src && src[i] && i + 1 < size)
	{
		dst[i] = src[i];
		++i;
	}
	if (i < size)
		dst[i] = '\0';
	return (dst);
}

static char	*ft_res_update_buf(char *line, char *buf, int rs)
{
	char	*old_mem;

	if (rs == -1)
		return (free(line), NULL);
	if (ft_gnlstrchr(line, '\n'))
	{
		*(ft_gnlstrchr(line, '\n') + 1) = '\0';
		old_mem = line;
		line = ft_gnlstrjoin("", line);
		free(old_mem);
	}
	if (line && !line[0])
	{
		free(line);
		line = NULL;
	}
	if (ft_gnlstrchr(buf, '\n'))
		ft_gnlstrlcpy(ft_gnlstrchr(buf, '\n') + 1, buf,
			ft_gnlstrchr(buf, '\0') - ft_gnlstrchr(buf, '\n') + 1);
	else
		buf[0] = '\0';
	return (line);
}

char	*parser_get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE] = "";
	char		*line;
	char		*old_mem;
	int			readsize;

	if (fd < 0)
		return (NULL);
	readsize = 1;
	line = ft_gnlstrjoin("", buffer);
	while (readsize > 0 && !ft_gnlstrchr(buffer, '\n'))
	{
		readsize = read(fd, buffer, BUFFER_SIZE);
		if (readsize > 0)
		{
			buffer[readsize] = '\0';
			old_mem = line;
			line = ft_gnlstrjoin(line, buffer);
			free(old_mem);
			if (!line)
				return (NULL);
		}
	}
	return (ft_res_update_buf(line, buffer, readsize));
}
