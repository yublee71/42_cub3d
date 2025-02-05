/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:48:23 by yublee            #+#    #+#             */
/*   Updated: 2025/02/05 20:08:33 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// raypos = pos + l * raydir
// static double	check_wall_hit(t_vars *vars, t_vec raydir, double lx, double ly, t_grid firstwall_grid)
// {
// 	t_vecset	vecset;
// 	int			move_grid_x;
// 	int			move_grid_y;
// 	int			i;
// 	int			hit;

// 	// t_vec		raypos;
// 	t_grid		grid;
// 	double		distance_x;
// 	double		distance_y;
// 	double		distance;

// 	vecset = vars->vecset;
// 	if (raydir.x > 0)
// 		move_grid_x = 1;
// 	else
// 		move_grid_x = -1;
// 	if (raydir.y > 0)
// 		move_grid_y = 1;
// 	else
// 		move_grid_y = -1;

// 	distance = 0;
// 	distance_x = 0;
// 	distance_y = 0;

// 	i = 0;
// 	hit = 0;
// 	while (1)
// 	{
// 		grid.x = firstwall_grid.x + i * move_grid_x;
// 		grid.y = (int) (vecset.pos.y + raydir.y * lx + 1 / tan(raydir.y / raydir.x * M_PI / 180) * (double)i * (double)move_grid_y);
// 		if (grid.x < 0 || grid.y < 0 || grid.x >= vars->map_width || grid.y >= vars->map_height)
// 			break ;
// 		if (vars->map[grid.x][grid.y] == '1')
// 		{
// 			hit = 1;
// 			break ;
// 		}
// 		i++;
// 	}
// 	printf("lx: grid x: %d, grid y: %d\n", grid.x, grid.y);
// 	if (hit)
// 		distance_x = lx * get_vector_length(raydir);

// 	i = 0;
// 	hit = 0;
// 	while (1)
// 	{
// 		grid.x = (int)(vecset.pos.x + raydir.x * ly + 1 / tan(raydir.y / raydir.x * M_PI / 180) * i * move_grid_x);
// 		grid.y = firstwall_grid.y + i * move_grid_y;
// 		if (grid.x < 0 || grid.y < 0 || grid.x >= vars->map_width || grid.y >= vars->map_height)
// 			break ;
// 		if (vars->map[grid.x][grid.y] == '1')
// 		{
// 			hit = 1;
// 			break;
// 		}
// 		i++;
// 	}
// 	printf("ly: grid x: %d, grid y: %d\n", grid.x, grid.y);
// 	if (hit)
// 		distance_y = ly * get_vector_length(raydir);

// 	if (distance_x < distance_y && distance_x)
// 		distance = distance_x;
// 	else if (distance_x > distance_y && distance_y)
// 		distance = distance_y;

// 	printf("distance: %f\n", distance);
// 	return (distance);
// }
// raydir = dir + k * plane
//raypos = pos + l * raydir

int	calculate_line_height(int i, t_vars *vars)
{
	t_vecset	vecset;
	t_vec		raydir;
	t_grid		pos_grid;
	t_grid		firstwall_grid;
	double		k;
	double		lx;
	double		ly;
	// double		distance;
	// double		line_height;

	vecset = vars->vecset;

	k = 2 * (double)i / (double)WINDOW_WIDTH - 1;
	// printf("k: %f\n", k);

	raydir.x = vecset.dir.x + k * vecset.plane.x;
	raydir.y = vecset.dir.y + k * vecset.plane.y;

	pos_grid.x = (int)vecset.pos.x;
	pos_grid.y = (int)vecset.pos.y;

	if (raydir.x > 0)
		firstwall_grid.x = pos_grid.x + 1;
	else
		firstwall_grid.x = pos_grid.x;
	if (raydir.y > 0)
		firstwall_grid.y = pos_grid.y + 1;
	else
		firstwall_grid.y = pos_grid.y;

	lx = (firstwall_grid.x - vecset.pos.x) / raydir.x;
	ly = (firstwall_grid.y - vecset.pos.y) / raydir.y;

	printf("firstwall_grid x: %d\n", firstwall_grid.x);
	printf("firstwall_grid y: %d\n", firstwall_grid.y);
	printf("lx: %f\n", lx);
	printf("ly: %f\n", ly);

	// distance = check_wall_hit(vars, raydir, lx, ly, firstwall_grid);
	// line_height = WINDOW_HEIGHT / distance;

	// printf("%f\n", line_height);
	return (0);
}