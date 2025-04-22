/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:30:23 by yublee            #+#    #+#             */
/*   Updated: 2025/04/22 15:56:49 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_distinfo	choose_dist(t_distinfo d_x, t_distinfo d_y, t_vec raydir)
{
	t_distinfo	distance_info;

	if ((d_x.distance_to_wall && d_y.distance_to_wall
			&& d_x.distance_to_wall < d_y.distance_to_wall)
		|| (d_x.distance_to_wall && !d_y.distance_to_wall))
	{
		distance_info = d_x;
		if (raydir.x > 0)
			distance_info.hit_direction = WEST;
		else
			distance_info.hit_direction = EAST;
	}
	else
	{
		distance_info = d_y;
		if (raydir.y > 0)
			distance_info.hit_direction = NORTH;
		else
			distance_info.hit_direction = SOUTH;
	}
	return (distance_info);
}

t_distinfo	get_dist_info_x(t_vars *vars, t_vecset vecset, t_vec raydir, t_grid sign)
{
	t_vec		firstwall_pos;
	t_grid		firstwall_grid;
	t_distinfo	dist_info;
	double		distance_to_grid_x;
	double		distance_to_wall_x;

	distance_to_wall_x = 0;
	if (sign.x > 0)
		firstwall_pos.x = (int)vecset.pos.x + 1;
	else
		firstwall_pos.x = (int)vecset.pos.x;
	distance_to_grid_x = fabs(firstwall_pos.x - vecset.pos.x);
	firstwall_pos.y = vecset.pos.y + distance_to_grid_x * fabs(raydir.y / raydir.x) * sign.y;
	firstwall_grid.y = (int)firstwall_pos.y;
	if (sign.x > 0)
		firstwall_grid.x = (int)firstwall_pos.x;
	else
		firstwall_grid.x = (int)firstwall_pos.x - 1;
	while (isinthemap(vars, firstwall_grid))
	{
		if (vars->map[firstwall_grid.y][firstwall_grid.x] == '1')
		{
			distance_to_wall_x = get_line_to_point_distance((vecset.plane.y / vecset.plane.x), vecset.pos, firstwall_pos);
			break ;
		}
		firstwall_pos.x += 1 * sign.x;
		firstwall_pos.y += fabs(raydir.y / raydir.x) * sign.y;
		if (sign.x > 0)
			firstwall_grid.x = (int)firstwall_pos.x;
		else
			firstwall_grid.x = (int)firstwall_pos.x - 1;
		firstwall_grid.y = (int)firstwall_pos.y;
	}
	dist_info.distance_to_wall = distance_to_wall_x;
	if (sign.x > 0)
		dist_info.distance_to_grid = fabs(firstwall_pos.y - firstwall_grid.y);
	else
		dist_info.distance_to_grid = 1 - fabs(firstwall_pos.y - firstwall_grid.y);
	return (dist_info);
}

t_distinfo	get_dist_info_y(t_vars *vars, t_vecset vecset, t_vec raydir, t_grid sign)
{
	t_vec		firstwall_pos;
	t_grid		firstwall_grid;
	t_distinfo	dist_info;
	double		distance_to_grid_y;
	double		distance_to_wall_y;

	distance_to_wall_y = 0;
	if (sign.y > 0)
		firstwall_pos.y = (int)vecset.pos.y + 1;
	else
		firstwall_pos.y = (int)vecset.pos.y;
	distance_to_grid_y = fabs(firstwall_pos.y - vecset.pos.y);
	firstwall_pos.x = vecset.pos.x + distance_to_grid_y / fabs(raydir.y / raydir.x) * sign.x;
	firstwall_grid.x = (int)firstwall_pos.x;
	if (sign.y > 0)
		firstwall_grid.y = (int)firstwall_pos.y;
	else
		firstwall_grid.y = (int)firstwall_pos.y - 1;
	while (isinthemap(vars, firstwall_grid))
	{
		if (vars->map[firstwall_grid.y][firstwall_grid.x] == '1')
		{
			distance_to_wall_y = get_line_to_point_distance((vecset.plane.y / vecset.plane.x), vecset.pos, firstwall_pos);
			break ;
		}
		firstwall_pos.y += 1 * sign.y;
		firstwall_pos.x += 1 / fabs(raydir.y / raydir.x) * sign.x;
		firstwall_grid.x = (int)firstwall_pos.x;
		if (sign.y > 0)
			firstwall_grid.y = (int)firstwall_pos.y;
		else
			firstwall_grid.y = (int)firstwall_pos.y - 1;
	}
	dist_info.distance_to_wall = distance_to_wall_y;
	if (sign.y > 0)
		dist_info.distance_to_grid = 1 - fabs(firstwall_pos.x - firstwall_grid.x);
	else
		dist_info.distance_to_grid = fabs(firstwall_pos.x - firstwall_grid.x);
	return (dist_info);
}
