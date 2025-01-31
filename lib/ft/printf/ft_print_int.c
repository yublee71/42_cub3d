/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:04:53 by yublee            #+#    #+#             */
/*   Updated: 2024/01/11 15:49:19 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	char	temp;

	temp = '0';
	if (nb < 0)
	{
		ft_write('-', 1);
		if (nb <= -10)
			ft_putnbr(-(nb / 10));
		ft_putnbr(-(nb % 10));
	}
	while (nb >= 10)
	{
		ft_putnbr(nb / 10);
		nb %= 10;
	}
	if (nb < 10 && nb >= 0)
	{
		temp += nb;
		ft_write(temp, 1);
	}
}

void	ft_print_int(char c, int i)
{
	if (c == 'd' || c == 'i')
		ft_putnbr(i);
	else if (c == 'c')
		ft_write(i, 1);
	else if (c == '%')
		ft_write(i, 1);
	else
		return ;
}
