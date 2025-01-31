/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:52:06 by yublee            #+#    #+#             */
/*   Updated: 2023/12/04 19:53:16 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * if s == NULL && (int == 0 || int != 0) : segfault
 * if s == "" && int == 0                 : returns ""
 * if s == "" && int != 0                 : returns NULL
 */

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	size_t	len_cpy;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	len_cpy = len;
	while (i <= len_cpy)
	{
		if (*(s + len) == (char)c)
			return ((char *)s + len);
		len--;
		i++;
	}
	return (NULL);
}
