/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:05:03 by yublee            #+#    #+#             */
/*   Updated: 2024/01/11 15:49:25 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char *str)
{
	while (*str)
	{
		ft_write(*str, 1);
		str++;
	}
}

void	ft_print_str(char *str)
{
	if (!str)
	{
		ft_putstr("(null)");
		return ;
	}
	ft_putstr(str);
}
