/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:05:29 by yublee            #+#    #+#             */
/*   Updated: 2024/01/11 15:49:37 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * %c 99 Prints a single character.
 * %s 115 Prints a string (as defined by the common C convention).
 * %p 112 The void * pointer argument has to be printed in hexadecimal format.
 * %d 100 Prints a decimal (base 10) number.
 * %i 105 Prints an integer in base 10.
 * %u 117 Prints an unsigned decimal (base 10) number.
 * %x 120 Prints a number in hexadecimal (base 16) lowercase format.
 * %X 88 Prints a number in hexadecimal (base 16) uppercase format.
 * %% 37 Prints a percent sign
 */

size_t	ft_write(char c, int n)
{
	static size_t	count = 0;
	size_t			count_cpy;

	if (n == 0)
	{
		count_cpy = count;
		count = 0;
		return (count_cpy);
	}
	else
	{
		write(1, &c, 1);
		count++;
		return (count);
	}
}

void	ft_whattype(char type, va_list args)
{
	if (type == 'd' || type == 'i' || type == 'c')
		ft_print_int(type, va_arg(args, int));
	else if (type == 'u' || type == 'x' || type == 'X')
		ft_print_unsignedint(type, va_arg(args, unsigned int));
	else if (type == 's')
		ft_print_str(va_arg(args, char *));
	else if (type == 'p')
		ft_print_ptr(va_arg(args, void *));
	else if (type == '%')
		ft_write(type, 1);
	else
		return ;
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	char		type;
	size_t		i;

	va_start(args, format);
	i = 0;
	while (format[i])
	{
		if (format[i] != '%')
			ft_write(format[i], 1);
		else if (format[++i])
		{
			type = format[i];
			ft_whattype(type, args);
		}
		i++;
	}
	va_end(args);
	return (ft_write(0, 0));
}
