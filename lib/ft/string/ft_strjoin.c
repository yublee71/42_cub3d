/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:50:26 by yublee            #+#    #+#             */
/*   Updated: 2023/11/20 19:38:12 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	charnum;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	charnum = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)malloc(charnum + 1);
	if (!new)
		return (NULL);
	*new = '\0';
	ft_strcat(new, s1);
	ft_strcat(new, s2);
	return (new);
}
