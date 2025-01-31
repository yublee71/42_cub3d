/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:48:50 by yublee            #+#    #+#             */
/*   Updated: 2023/11/17 18:55:31 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n == 0 || n < 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		minus;
	char	*result;

	len = ft_intlen(n);
	minus = 1;
	if (n < 0)
		minus *= -1;
	result = (char *)malloc(len + 1);
	if (!result)
		return (0);
	result[len] = '\0';
	while (--len >= 0)
	{
		if (minus > 0)
			result[len] = n % 10 + '0';
		else
			result[len] = - (n % 10) + '0';
		n /= 10;
	}
	if (minus == -1)
		result[0] = '-';
	return (result);
}
