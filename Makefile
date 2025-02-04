NAME			:= cub3d
CC				:= cc
MANDATORY_FLAGS	:= -Wall -Wextra -Werror
CFLAGS			:= $(MANDATORY_FLAGS)

SRCS			:= \
					src/main.c \
					src/keyhook.c \
					src/img_utils.c \
					src/utils.c \

BUILD_DIR		:= build
OBJS			:= $(SRCS:%.c=$(BUILD_DIR)/%.o)

RM				:= rm
RMFLAGS			:= -rf

LIBFT_DIR		:=  ./lib/ft
LIBFT_LIB		:=  $(LIBFT_DIR)/libft.a

MINILIB_DIR		:= ./lib/minilibx-linux
MINILIB_LIB		= $(MINILIB_DIR)/libmlx.a

INCLUDE			= -I $(MINILIB_DIR)

LINK_FLAGS		:= -L $(LIBFT_DIR) -L $(MINILIB_DIR) -lft -lmlx_Linux -lX11 -lXext -lm -lbsd

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(MINILIB_LIB) $(OBJS)
		$(CC) $(OBJS) -o $@ $(LINK_FLAGS)

$(LIBFT_LIB):
		@$(MAKE) -C $(LIBFT_DIR)

$(MINILIB_LIB):
	make -C $(MINILIB_DIR)

$(BUILD_DIR)/%.o: %.c
		@if [ ! -d $(@D) ]; then mkdir -pv $(@D); fi
		$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

clean:
		$(RM) $(RMFLAGS) $(BUILD_DIR)
		$(MAKE) -C $(LIBFT_DIR) clean
		$(MAKE) -C $(MINILIB_DIR) clean

fclean: clean
		$(RM) $(RMFLAGS) $(NAME)
		$(RM) $(RMFLAGS) $(LIBFT_LIB)
		$(RM) $(RMFLAGS) $(MINILIB_LIB)

re: fclean all

.PHONY: all clean fclean re bonus

