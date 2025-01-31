/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:49:55 by yublee            #+#    #+#             */
/*   Updated: 2023/11/20 17:45:22 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * if s == NULL && (int == 0 || int != 0) : segfault
 * if s == "" && int == 0                 : returns ""
 * if s == "" && int != 0                 : returns NULL
 */

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (*(s + i) == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
