/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:30:23 by yublee            #+#    #+#             */
/*   Updated: 2025/05/13 16:47:07 by yublee           ###   ########.fr       */
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
			distance_info.hit_direction = EAST;
		else
			distance_info.hit_direction = WEST;
	}
	else
	{
		distance_info = d_y;
		if (raydir.y > 0)
			distance_info.hit_direction = SOUTH;
		else
			distance_info.hit_direction = NORTH;
	}
	return (distance_info);
}

void	prepare_get_dist_info_x(t_vec *firstwall_pos, t_vecset vecset,
			t_vec raydir, t_grid sign)
{
	(*firstwall_pos).x = (int)vecset.pos.x + (sign.x > 0) * 1;
	(*firstwall_pos).y = vecset.pos.y + fabs((*firstwall_pos).x - vecset.pos.x)
		* fabs(raydir.y / raydir.x) * sign.y;
}

t_distinfo	get_dist_info_x(t_vars *vars, t_vecset vecset,
			t_vec raydir, t_grid sign)
{
	t_vec		firstwall_pos;
	t_grid		firstwall_grid;
	t_distinfo	dist_info;

	dist_info.distance_to_wall = 0;
	prepare_get_dist_info_x(&firstwall_pos, vecset, raydir, sign);
	firstwall_grid.y = (int)firstwall_pos.y;
	firstwall_grid.x = (int)firstwall_pos.x - (sign.x <= 0) * 1;
	while (isinthemap(vars, firstwall_grid))
	{
		if (vars->map[firstwall_grid.y][firstwall_grid.x] == '1')
		{
			dist_info.distance_to_wall = get_line_to_point_distance
				(vecset.plane.y / vecset.plane.x, vecset.pos, firstwall_pos);
			break ;
		}
		firstwall_pos.x += 1 * sign.x;
		firstwall_pos.y += fabs(raydir.y / raydir.x) * sign.y;
		firstwall_grid.x = (int)firstwall_pos.x - (sign.x <= 0) * 1;
		firstwall_grid.y = (int)firstwall_pos.y;
	}
	dist_info.distance_to_grid = 1 - fabs(firstwall_pos.y - firstwall_grid.y);
	if (sign.x > 0)
		dist_info.distance_to_grid = fabs(firstwall_pos.y - firstwall_grid.y);
	return (dist_info);
}

void	prepare_get_dist_info_y(t_vec *firstwall_pos, t_vecset vecset,
			t_vec raydir, t_grid sign)
{
	(*firstwall_pos).y = (int)vecset.pos.y + (sign.y > 0) * 1;
	(*firstwall_pos).x = vecset.pos.x + fabs((*firstwall_pos).y - vecset.pos.y)
		/ fabs(raydir.y / raydir.x) * sign.x;
}

t_distinfo	get_dist_info_y(t_vars *vars, t_vecset vecset,
		t_vec raydir, t_grid sign)
{
	t_vec		firstwall_pos;
	t_grid		firstwall_grid;
	t_distinfo	dist_info;

	dist_info.distance_to_wall = 0;
	prepare_get_dist_info_y(&firstwall_pos, vecset, raydir, sign);
	firstwall_grid.x = (int)firstwall_pos.x;
	firstwall_grid.y = (int)firstwall_pos.y - (sign.y <= 0) * 1 ;
	while (isinthemap(vars, firstwall_grid))
	{
		if (vars->map[firstwall_grid.y][firstwall_grid.x] == '1')
		{
			dist_info.distance_to_wall = get_line_to_point_distance
				(vecset.plane.y / vecset.plane.x, vecset.pos, firstwall_pos);
			break ;
		}
		firstwall_pos.y += 1 * sign.y;
		firstwall_pos.x += 1 / fabs(raydir.y / raydir.x) * sign.x;
		firstwall_grid.x = (int)firstwall_pos.x;
		firstwall_grid.y = (int)firstwall_pos.y - 1 * (sign.y <= 0);
	}
	dist_info.distance_to_grid = 1 - fabs(firstwall_pos.x - firstwall_grid.x);
	if (sign.y <= 0)
		dist_info.distance_to_grid = fabs(firstwall_pos.x - firstwall_grid.x);
	return (dist_info);
}
