/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:25:07 by yublee            #+#    #+#             */
/*   Updated: 2024/05/05 11:54:12 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_gnl_substr(char *s, size_t start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	size_t			strlen;
	char			*substring;

	if (!s || !len)
		return (NULL);
	i = start;
	j = 0;
	strlen = ft_strlen(s);
	if (!strlen || start > strlen)
	{
		substring = ft_strdup("");
		return (substring);
	}
	if (len < strlen - start)
		substring = (char *)malloc(len + 1);
	else
		substring = (char *)malloc(strlen - start + 1);
	if (!substring)
		return (NULL);
	while (s[i] && j < len)
		substring[j++] = s[i++];
	substring[j] = '\0';
	return (substring);
}

char	*ft_malloc(size_t n)
{
	char	*result;
	size_t	i;

	result = (char *)malloc(n);
	if (!result)
		return (NULL);
	i = 0;
	while (i < n)
		*((unsigned char *)result + i++) = 0;
	return (result);
}

char	*ft_f_strjoin(char *s1, char *s2)
{
	size_t	charnum;
	size_t	i;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	if (!*s2)
		return (s1);
	charnum = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(charnum + 1);
	if (!result)
		return (ft_free(&s1, s2));
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	i = -1;
	while (s2[++i])
		result[ft_strlen(s1) + i] = s2[i];
	result[charnum] = 0;
	free(s1);
	free(s2);
	return (result);
}
