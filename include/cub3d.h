/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:55:33 by yublee            #+#    #+#             */
/*   Updated: 2025/05/13 20:55:39 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <X11/keysymdef.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>

# define STR_ERR_MLX_INIT		"Error\nMLX initialization failed.\n"
# define STR_ERR_WINDOW_INIT	"Error\nWindow initialization failed.\n"
# define STR_ERR_IMG_INIT		"Error\nImage initialization failed.\n"
# define STR_ERR_IMG_OPEN		"Error\nImage file open failed.\n"

# define WINDOW_WIDTH	1280
# define WINDOW_HEIGHT	720

# define FOV			90 //Field of View
# define MOV_DIS		0.2
# define MOVE_ANGLE		6

# define YES 			1
# define NO 			0
# define ERR 			1
# define OK 			0

typedef struct s_grid
{
	int	x;
	int	y;
}	t_grid;

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

typedef struct s_distinfo
{
	double		distance_to_wall;
	double		distance_to_grid;
	t_cardinal	hit_direction;
}	t_distinfo;

typedef struct s_lineinfo
{
	t_distinfo	distance_info;
	int			line_height;
}	t_lineinfo;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	char		**map;
	int			map_width;
	int			map_height;
	t_img		img;
	t_img		assets[4];
	t_vecset	*vecset;
	t_colorset	colorset;
	int			exit_no;
}	t_vars;

typedef struct s_parse
{
	int			num_texture_colour;
	int			dir[4];
	int			ceiling;
	int			floor;
	t_cardinal	facing;
	t_list		*map;
	t_vars		*vars;
}	t_parse;

/*init*/
void		initialize_cub3d(t_vars *vars);

/*draw*/
void		draw_image(t_vars *vars);

/*calculate line height*/
t_lineinfo	get_line_info_by_dda(int i, t_vars *vars);

/*calculate distance*/
t_distinfo	choose_dist(t_distinfo d_x, t_distinfo d_y, t_vec raydir);
t_distinfo	get_dist_info_x(t_vars *vars, t_vecset vecset,
				t_vec raydir, t_grid sign);
t_distinfo	get_dist_info_y(t_vars *vars, t_vecset vecset,
				t_vec raydir, t_grid sign);

/*keyhook*/
int			handle_key_input(int keysym, t_vars *vars);

/*math utils*/
t_vec		rotate_vector(t_vec	vec, int degree);
double		convert_deg_to_rad(double degree);
double		get_vector_length(t_vec raydir);
double		get_line_to_point_distance(double tan, t_vec pos, t_vec dot);

/*map utils*/
int			isinthemap(t_vars *vars, t_grid grid);

/*exit*/
int			err_msg(char *msg, int return_val);
int			close_game(t_vars *vars);

/*vecset*/
t_vecset	get_vecset(double pos_x, double pos_y, t_cardinal direction);

/*parser*/
int			check_map_name(char *path);
char		*parser_get_next_line(int fd);
int			vars_parser(t_vars *vars, char *path);
char		*ft_remove_space(char *line);
void		empty_function(void *arg);
void		free_content(void *arg);
int			copy_to_map(t_parse *parse);
int			need_more_texture_colour(t_parse *parse);
int			texture_colour_handler(t_parse *parse, char *line);
int			map_line_handler(t_parse *parse, char *line);
int			map_not_closed(t_vars *vars);
int			texture_handler(t_parse *parse, char *line, int type);
int			colour_handler(t_parse *parse, char *line, int *colour, int *type);
void		revert_map(t_vars *vars);

#endif