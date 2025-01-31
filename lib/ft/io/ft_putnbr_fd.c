/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:05:33 by yublee            #+#    #+#             */
/*   Updated: 2023/11/16 18:33:23 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	temp;

	temp = '0';
	if (n < 0)
	{
		write(fd, "-", 1);
		if (n <= -10)
			ft_putnbr_fd(-(n / 10), fd);
		ft_putnbr_fd(-(n % 10), fd);
	}
	while (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		n %= 10;
	}
	if (n < 10 && n >= 0)
	{
		temp += n;
		write(fd, &temp, 1);
	}
}
