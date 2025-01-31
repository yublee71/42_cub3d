/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:52:20 by yublee            #+#    #+#             */
/*   Updated: 2023/11/20 19:26:03 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	size_t			strlen;
	char			*substring;

	if (!s)
		return (NULL);
	i = start;
	j = 0;
	strlen = ft_strlen(s);
	if (!strlen || !len || start > strlen)
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
