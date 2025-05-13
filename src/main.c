/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:46:40 by yublee            #+#    #+#             */
/*   Updated: 2025/05/13 20:55:49 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_vecset	get_vecset(double pos_x, double pos_y, t_cardinal direction)
{
	t_vecset	vecset;

	vecset.pos.x = pos_x;
	vecset.pos.y = pos_y;
	vecset.dir.x = 0;
	vecset.dir.y = -1;
	vecset.plane.x = tan(convert_deg_to_rad(FOV / 2));
	vecset.plane.y = 0;
	if (direction == SOUTH)
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
	return (vecset);
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	t_vecset	vecset;

	ft_bzero(&vars, sizeof(t_vars));
	if (argc != 2)
		return (err_msg("Error\nIncorrect number of arguments\n", 1));
	initialize_cub3d(&vars);
	vars.vecset = &vecset;
	vecset.pos.x = -1;
	vecset.pos.y = -1;
	if (check_map_name(argv[1]))
		return (close_game(&vars), 1);
	if (vars_parser(&vars, argv[1]))
		return (close_game(&vars), 1);
	draw_image(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
	mlx_hook(vars.win, 2, 1L << 0, handle_key_input, &vars);
	mlx_hook(vars.win, 17, 1L << 2, close_game, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
