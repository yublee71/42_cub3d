/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:50:04 by yublee            #+#    #+#             */
/*   Updated: 2024/08/06 23:47:57 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_strdup() function returns a pointer to a new string which is
 * a duplicate of the string s.
 * Memory for the new string is obtained with malloc(3), and can be freed
 * with free(3).
 */

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	srclen;

	srclen = ft_strlen(s);
	dest = (char *)malloc(srclen + 1);
	if (dest == NULL)
		return (NULL);
	while (*s)
		*dest++ = *s++;
	*dest = '\0';
	return (dest - srclen);
}
