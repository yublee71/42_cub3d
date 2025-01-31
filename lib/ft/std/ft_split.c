/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:49:44 by yublee            #+#    #+#             */
/*   Updated: 2023/11/20 19:39:29 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*ft_copytil(char const *s, char c)
{
	size_t	len;
	size_t	i;
	char	*result;

	len = 0;
	i = 0;
	while (s[len] != c && s[len])
		len++;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	**ft_split(char const *s, char c)
{
	size_t	wordcount;
	size_t	i;
	char	**result;

	if (!s)
		return (NULL);
	wordcount = ft_wordcount(s, c);
	result = (char **)malloc((wordcount + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < wordcount)
	{
		while (*s == c)
			s++;
		if (*s)
			result[i] = ft_copytil(s, c);
		while (*s != c && *s)
			s++;
		i++;
	}
	result[i] = NULL;
	return (result);
}
