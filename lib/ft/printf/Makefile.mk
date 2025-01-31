# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yublee <yublee@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/16 00:38:57 by yublee            #+#    #+#              #
#    Updated: 2024/06/18 00:27:27 by yublee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ft_printf sources

FILES   = ft_printf.c \
			ft_print_int.c \
			ft_print_str.c \
			ft_print_unsigned.c

SRCS    += $(FILES:%.c=$(dir $(lastword $(MAKEFILE_LIST)))%.c)
