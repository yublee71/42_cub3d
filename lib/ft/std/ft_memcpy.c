/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:49:19 by yublee            #+#    #+#             */
/*   Updated: 2023/11/17 17:29:48 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void *const	dst = dest;

	if (!dest && !src)
		return (NULL);
	while (n--)
		*(unsigned char *)dest++ = *(unsigned char *)src++;
	return (dst);
}
