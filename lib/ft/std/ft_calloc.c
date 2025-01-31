/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:44:39 by yublee            #+#    #+#             */
/*   Updated: 2023/11/16 18:30:22 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	size_t	i;
	void	*array;

	i = 0;
	total_size = nmemb * size;
	if (total_size && (total_size < nmemb || total_size < size))
		return (NULL);
	array = (void *)malloc(total_size);
	if (!array)
		return (NULL);
	while (i < total_size)
		*((unsigned char *)array + i++) = 0;
	return (array);
}
