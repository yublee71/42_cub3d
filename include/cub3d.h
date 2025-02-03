/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:55:33 by yublee            #+#    #+#             */
/*   Updated: 2025/02/03 19:27:33 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <stdio.h>
# include <X11/keysymdef.h>
# include <X11/keysym.h>

# define STR_ERR_MLX_INIT		"Error: MLX initialization failed.\n"
# define STR_ERR_WINDOW_INIT	"Error: Window initialization failed.\n"

# define WINDOW_WIDTH	1280
# define WINDOW_HEIGHT	720

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
	void	*mlx;
	void	*win;
	// char	**map;
	// t_img	*imgs;
}	t_vars;

int		handle_key_input(int keysym, t_vars *vars);
int		err_msg(char *msg, int return_val);
int		close_game(t_vars *vars);

#endif