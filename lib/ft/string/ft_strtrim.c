/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:52:14 by yublee            #+#    #+#             */
/*   Updated: 2023/11/20 19:39:07 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_charcheck(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	left;
	size_t	right;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	left = 0;
	right = ft_strlen(s1) - 1;
	while (s1[left] && ft_charcheck(set, s1[left]))
		left++;
	if (left < right)
		while (ft_charcheck(set, s1[right]))
			right--;
	result = ft_substr(s1, left, right - left + 1);
	return (result);
}
