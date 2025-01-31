# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yublee <yublee@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/16 00:38:57 by yublee            #+#    #+#              #
#    Updated: 2024/07/02 17:57:38 by yublee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES   = get_next_line.c \
			get_next_line_utils.c

SRCS    += $(FILES:%.c=$(dir $(lastword $(MAKEFILE_LIST)))%.c)
