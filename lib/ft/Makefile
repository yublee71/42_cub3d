# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yublee <yublee@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/18 14:44:19 by yublee            #+#    #+#              #
#    Updated: 2024/08/01 23:06:26 by yublee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -gdwarf-3
RM			= rm -fv
AR			= ar
ARFLAGS		= rcs
INCLUDE		= -I. -I./include

SRCS		:=
BONUS_SRCS	:=
BUILD_DIR	= build
DIRS		= bonus ctype gnl io printf std string

include $(addsuffix /Makefile.mk,$(DIRS))

OBJ			= $(SRCS:%.c=$(BUILD_DIR)/%.o)
BOBJ		= $(BONUS_SRCS:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ) $(BOBJ)
		$(AR) $(ARFLAGS) $(NAME) $(OBJ) $(BOBJ)

$(BUILD_DIR)/%.o: %.c
		@if [ ! -d $(@D) ]; then mkdir -pv $(@D); fi
		$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

clean:
		$(RM) -rf $(BUILD_DIR)

fclean: clean
		$(RM) $(NAME)

re: fclean all

norm:
		@norminette $(SRCS) $(BONUS_SRCS)

.PHONY: all clean fclean re
