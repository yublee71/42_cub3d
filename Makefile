NAME			:= cub3d
CC				:= cc
MANDATORY_FLAGS	:= -Wall -Wextra -Werror
DEBUG_FLAGS		:= -g
CFLAGS			:= $(MANDATORY_FLAGS) $(DEBUG_FLAGS)

SRCS			:= \
					src/main.c \
					src/init.c \
					src/img_draw.c \
					src/dda.c \
					src/dda_distance.c \
					src/keyhook.c \
					src/utils_math.c \
					src/utils_map.c \
					src/exit.c \
					src/parser.c \

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

