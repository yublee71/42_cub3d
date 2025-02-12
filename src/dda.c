/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:48:23 by yublee            #+#    #+#             */
/*   Updated: 2025/02/12 13:50:22 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_lineinfo	compare_distances(double distance_x, double distance_y)
{
	t_lineinfo dist_info;

	if (distance_x && distance_y)
	{
		if (distance_x < distance_y)
		{
			dist_info.distance = distance_x;
			dist_info.x_or_y = -1;
		}
		else
		{
			dist_info.distance = distance_y;
			dist_info.x_or_y = 1;
		}
	}
	else
	{
		if (distance_x)
		{
			dist_info.distance = distance_x;
			dist_info.x_or_y = -1;
		}
		else
		{
			dist_info.distance = distance_y;
			dist_info.x_or_y = 1;
		}
	}
	return dist_info;
}

//x>0 y>0
static double		get_distance_to_the_wall_x(t_vars *vars, t_vec raydir, double raydir_tan)
{
	t_vecset	vecset;
	t_vec		firstwall_pos;
	t_grid		firstwall_grid;
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
			distance_x = get_vector_to_vector_distance(vecset.pos, firstwall_pos);
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
	return (distance_x);
}

static double		get_distance_to_the_wall_y(t_vars *vars, t_vec raydir, double raydir_tan)
{
	t_vecset	vecset;
	t_vec		firstwall_pos;
	t_grid		firstwall_grid;
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
			distance_y = get_vector_to_vector_distance(vecset.pos, firstwall_pos);
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
	return (distance_y);
}

static t_lineinfo	get_distance_to_the_wall(t_vars *vars, t_vec raydir, double raydir_tan)
{
	double	distance_x;
	double	distance_y;
	
	distance_x = get_distance_to_the_wall_x(vars, raydir, raydir_tan);
	distance_y = get_distance_to_the_wall_y(vars, raydir, raydir_tan);
	return (compare_distances(distance_x, distance_y));
}

// raypos = pos + l * raydir
// raydir = dir + k * plane
t_lineinfo	calculate_line_height(int i, t_vars *vars)
{
	t_vecset	vecset;
	t_vec		raydir;
	double		k;
	t_lineinfo	dist_info;
	double		distance;
	double		distorted_angle;
	int			line_height;

	vecset = *vars->vecset;

	k = 2 * (double)i / (double)WINDOW_WIDTH - 1;
	// printf("k: %f\n", k);

	raydir.x = vecset.dir.x + k * vecset.plane.x;
	raydir.y = vecset.dir.y + k * vecset.plane.y;

	// printf("lx: %f\n", lx);
	// printf("ly: %f\n", ly);

	dist_info = get_distance_to_the_wall(vars, raydir, fabs(raydir.y / raydir.x));

	if (dist_info.x_or_y < 0)
	{
		if (raydir.x > 0)
			dist_info.hit_direction = 3;
		else
			dist_info.hit_direction = 2;
	}
	else
	{
		if (raydir.y > 0)
			dist_info.hit_direction = 0;
		else
			dist_info.hit_direction = 1;
	}
	distance = dist_info.distance;
	if (i < WINDOW_WIDTH / 2)
		distorted_angle = (double)FOV / 2 - i * (double)FOV / WINDOW_WIDTH;
	else
		distorted_angle = (double)FOV / 2 - (WINDOW_WIDTH - i) * (double)FOV / WINDOW_WIDTH;
		// printf("i: %d\n", i);
		// printf("angle: %f\n", cos(convert_deg_to_rad(distorted_angle)));

	distance = 1.5 * distance * cos(convert_deg_to_rad(distorted_angle));
	// printf("distance: %f\n", distance);
	line_height = 0;
	if (distance)
		line_height = WINDOW_HEIGHT / distance;
	// printf("line_height: %f\n", line_height);
	dist_info.line_height = line_height;

	return (dist_info);
}