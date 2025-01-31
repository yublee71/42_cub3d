/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:48:14 by yublee            #+#    #+#             */
/*   Updated: 2023/10/17 21:01:38 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Copy src to dest, truncating or null-padding to always copy n bytes.
 * Return dest.
 * If there is no terminating null byte in the first n bytes of src, strncpy()
 * produces an unterminated string in dest.
 * `const char*` is a mutable pointer to an immutable character/string.
 * You cannot change the contents of the location(s) this pointer points to.
 */
char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	const char		*s = src;
	char *const		save_pointer = dest;
	unsigned int	i;

	i = 0;
	while (*s && (i++ < n))
		*dest++ = *s++;
	while (i++ < n)
		*dest++ = '\0';
	return (save_pointer);
}

/**
 * The  ft_strncat() function  appends at most n bytes from src string to
 * the dest string, overwriting the terminating null byte ('\0') at the end
 * of dest, and then adds a terminating null byte. The strings may not overlap,
 * and the dest string must have enough space for the result. The src does not
 * need to be null-terminated if it contains n or more bytes.
 * The resulting string in dest is always null-terminated.
 * If  src  contains  n or more bytes, strncat() writes n+1 bytes to dest
 * (n from src plus the terminating null byte).
 * Therefore, the size of dest must be at least strlen(dest)+n+1.
 */
char	*ft_strncat(char *dest, const char *src, unsigned int nb)
{
	char *const		save_pointer = dest;

	while (*dest)
		dest++;
	ft_strncpy(dest, src, nb);
	return (save_pointer);
}
