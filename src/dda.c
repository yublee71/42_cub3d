/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:48:23 by yublee            #+#    #+#             */
/*   Updated: 2025/02/10 16:17:24 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// raypos = pos + l * raydir
static t_distanceinfo	get_distance_to_the_wall(t_vars *vars, t_vec raydir)
{
	t_distanceinfo	distance;
	double	raydir_tan;

	raydir_tan = fabs(raydir.y / raydir.x);
	if (raydir.x > 0)
	{
		if (raydir.y > 0)
			distance = get_distance_to_the_wall_case1(vars, raydir_tan);
		else
			distance = get_distance_to_the_wall_case2(vars, raydir_tan);
	}
	else
	{
		if (raydir.y > 0)
			distance = get_distance_to_the_wall_case3(vars, raydir_tan);
		else
			distance = get_distance_to_the_wall_case4(vars, raydir_tan);
	}
	return distance;
}

// raydir = dir + k * plane
t_lineinfo	calculate_line_height(int i, t_vars *vars)
{
	t_lineinfo	line_info;
	t_vecset	vecset;
	t_vec		raydir;
	double		k;
	t_distanceinfo	dist_info;
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

	dist_info = get_distance_to_the_wall(vars, raydir);

	if (dist_info.x_or_y < 0)
	{
		if (raydir.x > 0)
			line_info.hit_direction = 3;
		else
			line_info.hit_direction = 2;
	}
	else
	{
		if (raydir.y > 0)
			line_info.hit_direction = 0;
		else
			line_info.hit_direction = 1;
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
	line_info.line_height = line_height;

	return (line_info);
}