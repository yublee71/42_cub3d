/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:50:04 by yublee            #+#    #+#             */
/*   Updated: 2024/08/06 23:54:12 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dest;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	if (len > n)
		len = n;
	dest = (char *)malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
