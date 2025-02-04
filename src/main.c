/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:46:40 by yublee            #+#    #+#             */
/*   Updated: 2025/02/04 16:13:00 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* this section will be removed later */

#define MAP_H 6
#define PATH_TO_IMAGE_N "./assets/n.xpm"
#define PATH_TO_IMAGE_S "./assets/s.xpm"
#define PATH_TO_IMAGE_E "./assets/e.xpm"
#define PATH_TO_IMAGE_W "./assets/w.xpm"

char *map[MAP_H + 1] = {
	"111111",
	"100001",
	"100001",
	"100001",
	"100001",
	"111111",
	NULL
};

/* ********************************** */

static t_vecset get_vecset(int pos_x, int pos_y, t_cardinal direction)
{
	t_vecset vecset;

	vecset.pos.x = pos_x;
	vecset.pos.y = pos_y;
	if (direction == NORTH)
	{
		vecset.dir.x = 0;
		vecset.dir.y = -1;
		vecset.plane.x = tan(FOV/2);
		vecset.plane.y = 0;
	}
	else if (direction == SOUTH)
	{
		vecset.dir.x = 0;
		vecset.dir.y = 1;
		vecset.plane.x = -tan(FOV/2);
		vecset.plane.y = 0;
	}
	else if (direction == EAST)
	{
		vecset.dir.x = 1;
		vecset.dir.y = 0;
		vecset.plane.x = 0;
		vecset.plane.y = tan(FOV/2);
	}
	else if (direction == WEST)
	{
		vecset.dir.x = -1;
		vecset.dir.y = 0;
		vecset.plane.x = 0;
		vecset.plane.y = -tan(FOV/2);
	}
	return vecset;
}

static void	get_assets(t_vars *vars)
{
	vars->assets[0] = get_img_from_file(PATH_TO_IMAGE_N, *vars);
	vars->assets[1] = get_img_from_file(PATH_TO_IMAGE_S, *vars);
	vars->assets[2] = get_img_from_file(PATH_TO_IMAGE_E, *vars);
	vars->assets[3] = get_img_from_file(PATH_TO_IMAGE_W, *vars);
}

static void	initialize_image(t_vars *vars)
{
	t_img	image;

	image.img_ptr = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	image.img_pixels_ptr = mlx_get_data_addr(image.img_ptr,
			&(image.bits_per_pixel), &(image.size_line), &(image.endian));
	image.width = WINDOW_WIDTH;
	image.height = WINDOW_HEIGHT;
	vars->img = image;
}

static int	initialize_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (err_msg(STR_ERR_MLX_INIT, -1));
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "CUB3D");
	if (!vars->win)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		return (err_msg(STR_ERR_WINDOW_INIT, -1));
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_vars		vars;

	(void)argc;
	(void)argv;
	vars.map = map; //TODO: remove
	vars.vecset = get_vecset(3, 3, NORTH); //TODO: get args parser
	if (initialize_window(&vars) < 0)
		return (EXIT_FAILURE);
	initialize_image(&vars);
	get_assets(&vars);
	draw_image(vars.img);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
	mlx_key_hook(vars.win, handle_key_input, &vars);
	mlx_hook(vars.win, 17, 1L << 2, close_game, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
