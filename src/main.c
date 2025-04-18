/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:46:40 by yublee            #+#    #+#             */
/*   Updated: 2025/04/18 22:18:17 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*TODO: modify after parser*/

char	*map[MAP_H + 1] = {
	"111111",
	"110011",
	"100101",
	"10P001", //(2, 3) -> (2.5, 3.5)
	"110011",
	"111111",
	NULL
};

t_vecset	get_vecset(double pos_x, double pos_y, t_cardinal direction)
{
	t_vecset	vecset;

	vecset.pos.x = pos_x;
	vecset.pos.y = pos_y;
	vecset.dir.x = 0;
	vecset.dir.y = -1;
	vecset.plane.x = tan(convert_deg_to_rad(FOV / 2));
	vecset.plane.y = 0;
	if (direction == NORTH)
		;
	else if (direction == SOUTH)
	{
		vecset.dir = rotate_vector(vecset.dir, 180);
		vecset.plane = rotate_vector(vecset.plane, 180);
	}
	else if (direction == EAST)
	{
		vecset.dir = rotate_vector(vecset.dir, 90);
		vecset.plane = rotate_vector(vecset.plane, 90);
	}
	else if (direction == WEST)
	{
		vecset.dir = rotate_vector(vecset.dir, -90);
		vecset.plane = rotate_vector(vecset.plane, -90);
	}
	/*TODO:remove*/
	printf("pos x: %f\n", vecset.pos.x);
	printf("pos y: %f\n", vecset.pos.y);
	printf("dir x: %f\n", vecset.dir.x);
	printf("dir y: %f\n", vecset.dir.y);
	printf("plane x: %f\n", vecset.plane.x);
	printf("plane y: %f\n", vecset.plane.y);
	/**************/
	return (vecset);
}

static t_colorset	get_colorset(int color1, int color2)
{
	t_colorset	colorset;

	colorset.color_ceiling = color1;
	colorset.color_floor = color2;
	return (colorset);
}

/***************************/

int	main(int argc, char **argv)
{
	t_vars		vars;
	t_vecset	vecset;

	/*TODO: get from parser*/
	// vars.map = map;
	// vars.map_height = MAP_H;
	// vars.map_width = MAP_W;
	// vecset = get_vecset(2.5, 3.5, NORTH);
	// vars.vecset = &vecset;
	// vars.colorset = get_colorset((int)0xffe6dcd1, (int)0xff2b1904);
	/********************* */

	ft_bzero(&vars, sizeof(t_vars));
	if (argc != 2)
		return (1);
	initialize_cub3d(&vars);
	vars.vecset = &vecset;
	vecset.pos.x = -1;
	vecset.pos.y = -1;
	if (vars_parser(&vars, argv[1]))
		return (1);
	draw_image(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
	mlx_hook(vars.win, 2, 1L << 0, handle_key_input, &vars);
	// mlx_key_hook(vars.win, handle_key_input, &vars);
	mlx_hook(vars.win, 17, 1L << 2, close_game, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
