/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:34:37 by yublee            #+#    #+#             */
/*   Updated: 2024/07/02 16:34:39 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Function  copies the string pointed to by src, including the terminating
 * null byte ('\0'), to the buffer  pointed  to  by  dest.
 * The strcpy() function returns a pointer to the destination string dest.
 * The strings  may  not overlap, and the destination string dest must be
 * large enough to receive the copy. If the destination string of a strcpy()
 * is not large enough, then anything might happen.
 * `char *const` is an immutable pointer (it cannot point to any other location)
 * but the contents of location at which it points are mutable.
 * stackoverflow.com/questions/9834067/difference-between-char-and-const-char
 */
char	*ft_strcpy(char *dest, const char *src)
{
	char *const	save = dest;

	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (save);
}

char	*ft_strcat(char *dest, const char *src)
{
	return (ft_strcpy(dest + ft_strlen(dest), src));
}
