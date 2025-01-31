/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:07:41 by yublee            #+#    #+#             */
/*   Updated: 2023/11/20 18:05:51 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * if (src == NULL && size == whatever) : segfault
 * if (dest == NULL && size == 0)       : behave normally
 * if (dest == NULL && size != 0)       : segfault
 */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (*src++)
		j++;
	return (j);
}
