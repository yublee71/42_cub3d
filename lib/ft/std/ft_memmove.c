/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:49:33 by yublee            #+#    #+#             */
/*   Updated: 2023/11/20 19:33:52 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * if ((dest == NULL || src == NULL) && n != 0) : segfault
 * if ((dest == NULL || src == NULL) && n == 0) : return NULL
 */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest <= src)
	{
		while (i < n)
		{
			*((unsigned char *)dest + i) = *((unsigned char *)src + i);
			i++;
		}
	}
	else
	{
		while (n)
		{
			n--;
			*((unsigned char *)dest + n) = *((unsigned char *)src + n);
			if (n == 0)
				break ;
		}
	}
	return (dest);
}
