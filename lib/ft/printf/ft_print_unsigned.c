/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:05:13 by yublee            #+#    #+#             */
/*   Updated: 2024/01/11 15:49:31 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	base_is(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		j = i + 1;
		if (base[i] == '+' || base[i] == '-')
			return (0);
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	if (i <= 1)
		return (0);
	return (i);
}

void	ft_putunsignednbr_base(long unsigned int nbr, char *base)
{
	long unsigned int	b;

	b = base_is(base);
	if (b)
	{
		if (nbr >= b)
		{
			ft_putunsignednbr_base(nbr / b, base);
			ft_putunsignednbr_base(nbr % b, base);
		}
		else
			ft_write(*(base + nbr), 1);
	}
}

void	ft_print_unsignedint(char c, unsigned int i)
{
	if (c == 'u')
		ft_putunsignednbr_base(i, "0123456789");
	else if (c == 'x')
		ft_putunsignednbr_base(i, "0123456789abcdef");
	else if (c == 'X')
		ft_putunsignednbr_base(i, "0123456789ABCDEF");
	else
		return ;
}

void	ft_print_ptr(void *ptr)
{
	if (!ptr)
	{
		ft_print_str("(nil)");
		return ;
	}
	else
	{
		ft_print_str("0x");
		ft_putunsignednbr_base((long unsigned int)ptr, "0123456789abcdef");
	}
}
