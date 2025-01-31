/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:50:41 by yublee            #+#    #+#             */
/*   Updated: 2023/11/20 18:02:32 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * if (src == NULL && size == whatever) : segfault
 * if (dest == NULL && size == 0)       : behave normally
 * if (dest == NULL && size != 0)       : segfault
 */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	size_src;
	size_t	size_dst;

	size_src = ft_strlen(src);
	if (!dst && !size)
		return (size_src + size);
	size_dst = ft_strlen(dst);
	if (size_dst >= size)
		return (size_src + size);
	i = 0;
	while (src[i] && i < size - size_dst - 1)
	{
		dst[size_dst + i] = src[i];
		i++;
	}
	dst[size_dst + i] = '\0';
	return (size_src + size_dst);
}
