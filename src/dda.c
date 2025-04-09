/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:48:23 by yublee            #+#    #+#             */
/*   Updated: 2025/04/09 15:04:33 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_distinfo	choose_dist(t_distinfo d_x, t_distinfo d_y, t_vec raydir)
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

static	t_distinfo	get_dist_info_x(t_vars *vars, t_vec raydir, double raydir_tan)
{
	t_vecset	vecset;
	t_vec		firstwall_pos;
	t_grid		firstwall_grid;
	t_distinfo	dist_info;
	double		dx;
	double		distance_x;
	int			sign_x;
	int			sign_y;

	vecset = *vars->vecset;
	distance_x = 0;
	sign_x = raydir.x / fabs(raydir.x);
	sign_y = raydir.y / fabs(raydir.y);
	if (sign_x > 0)
		firstwall_pos.x = (int)vecset.pos.x + 1;
	else
		firstwall_pos.x = (int)vecset.pos.x;
	dx = fabs(firstwall_pos.x - vecset.pos.x);
	firstwall_pos.y = vecset.pos.y + dx * raydir_tan * sign_y;
	if (sign_x > 0)
		firstwall_grid.x = (int)firstwall_pos.x;
	else
		firstwall_grid.x = (int)firstwall_pos.x - 1;
	firstwall_grid.y = (int)firstwall_pos.y;
	while (isinthemap(vars, firstwall_grid))
	{
		if (vars->map[firstwall_grid.y][firstwall_grid.x] == '1')
		{
			distance_x = get_line_to_point_distance((vecset.plane.y / vecset.plane.x), vecset.pos, firstwall_pos);
			break ;
		}
		firstwall_pos.x += 1 * sign_x;
		firstwall_pos.y += raydir_tan * sign_y;
		if (sign_x > 0)
			firstwall_grid.x = (int)firstwall_pos.x;
		else
			firstwall_grid.x = (int)firstwall_pos.x - 1;
		firstwall_grid.y = (int)firstwall_pos.y;
	}
	dist_info.distance_to_wall = distance_x;
	if (sign_x > 0)
		dist_info.distance_to_grid = fabs(firstwall_pos.y - firstwall_grid.y);
	else
		dist_info.distance_to_grid = 1 - fabs(firstwall_pos.y - firstwall_grid.y);
	return (dist_info);
}

static t_distinfo	get_dist_info_y(t_vars *vars, t_vec raydir, double raydir_tan)
{
	t_vecset	vecset;
	t_vec		firstwall_pos;
	t_grid		firstwall_grid;
	t_distinfo	dist_info;
	double		distance_y;
	double		dy;
	int			sign_x;
	int			sign_y;

	vecset = *vars->vecset;
	distance_y = 0;
	sign_x = raydir.x / fabs(raydir.x);
	sign_y = raydir.y / fabs(raydir.y);
	if (sign_y > 0)
		firstwall_pos.y = (int)vecset.pos.y + 1;
	else
		firstwall_pos.y = (int)vecset.pos.y;
	dy = fabs(firstwall_pos.y - vecset.pos.y);
	firstwall_pos.x = vecset.pos.x + dy / raydir_tan * sign_x;
	firstwall_grid.x = (int)firstwall_pos.x;
	if (sign_y > 0)
		firstwall_grid.y = (int)firstwall_pos.y;
	else
		firstwall_grid.y = (int)firstwall_pos.y - 1;
	while (isinthemap(vars, firstwall_grid))
	{
		if (vars->map[firstwall_grid.y][firstwall_grid.x] == '1')
		{
			distance_y = get_line_to_point_distance((vecset.plane.y / vecset.plane.x), vecset.pos, firstwall_pos);
			break ;
		}
		firstwall_pos.y += 1 * sign_y;
		firstwall_pos.x += 1 / raydir_tan * sign_x;
		firstwall_grid.x = (int)firstwall_pos.x;
		if (sign_y > 0)
			firstwall_grid.y = (int)firstwall_pos.y;
		else
			firstwall_grid.y = (int)firstwall_pos.y - 1;
	}
	dist_info.distance_to_wall = distance_y;
	if (sign_y > 0)
		dist_info.distance_to_grid = 1 - fabs(firstwall_pos.x - firstwall_grid.x);
	else
		dist_info.distance_to_grid = fabs(firstwall_pos.x - firstwall_grid.x);
	return (dist_info);
}

static t_lineinfo	calculate_by_dda(t_vars *vars, t_vec raydir)
{
	double		raydir_tan;
	t_distinfo	distance_x;
	t_distinfo	distance_y;
	t_lineinfo	line_info;
	double		line_height;

	raydir_tan = fabs(raydir.y / raydir.x);
	distance_x = get_dist_info_x(vars, raydir, raydir_tan);
	distance_y = get_dist_info_y(vars, raydir, raydir_tan);
	line_info.distance_info = choose_dist(distance_x, distance_y, raydir);
	line_height = 0;
	if (line_info.distance_info.distance_to_wall)
		line_height = WINDOW_HEIGHT / line_info.distance_info.distance_to_wall;
	line_info.line_height = line_height;
	return (line_info);
}

// DDA: Digital Differential Analysis - line drawing algorithm in graphics
// raydir = dir + k * plane (k: -1 ~ 1)
t_lineinfo	get_line_info_by_dda(int i, t_vars *vars)
{
	t_vecset	vecset;
	t_vec		raydir;
	double		k;
	t_lineinfo	line_info;

	vecset = *vars->vecset;
	k = -1 + 2 * (double)i / (double)WINDOW_WIDTH;
	raydir.x = vecset.dir.x + k * vecset.plane.x;
	raydir.y = vecset.dir.y + k * vecset.plane.y;
	line_info = calculate_by_dda(vars, raydir);
	return (line_info);
}
