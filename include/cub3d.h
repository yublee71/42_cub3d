/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:55:33 by yublee            #+#    #+#             */
/*   Updated: 2025/02/05 14:51:58 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <stdio.h>
# include <math.h>
# include <X11/keysymdef.h>
# include <X11/keysym.h>

# define STR_ERR_MLX_INIT		"Error: MLX initialization failed.\n"
# define STR_ERR_WINDOW_INIT	"Error: Window initialization failed.\n"

# define WINDOW_WIDTH	1280
# define WINDOW_HEIGHT	720

# define FOV			60
# define MOVE_DISTANCE	10
# define MOVE_ANGLE		10

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_vecset
{
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
}	t_vecset;

typedef struct s_colorset
{
	int	color_floor;
	int	color_ceiling;
}	t_colorset;

typedef enum e_cardinal
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3,
}	t_cardinal;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		height;
	int		width;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_vars
{
	void		*mlx; //needs free
	void		*win; //needs free
	char		**map;
	t_img		img; //needs free
	t_img		assets[4]; //needs free
	t_vecset	vecset;
	t_colorset	colorset;
}	t_vars;

void	draw_image_with_color(t_vars *vars);
// t int		calculate_line_height(int i, t_vars vars);
t_img	get_img_from_file(char *file_name, t_vars vars);
int		handle_key_input(int keysym, t_vars *vars);
int		err_msg(char *msg, int return_val);
int		close_game(t_vars *vars);

#endif