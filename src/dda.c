/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:48:23 by yublee            #+#    #+#             */
/*   Updated: 2025/02/07 18:35:31 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// raypos = pos + l * raydir
static double	get_distance_to_the_wall(t_vars *vars, t_vec raydir)
{
	double	distance;
	double	raydir_tan;

	(void) vars;
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
int	calculate_line_height(int i, t_vars *vars)
{
	t_vecset	vecset;
	t_vec		raydir;
	double		k;
	double		distance;
	double		line_height;

	vecset = *vars->vecset;

	k = 2 * (double)i / (double)WINDOW_WIDTH - 1;
	printf("k: %f\n", k);

	raydir.x = vecset.dir.x + k * vecset.plane.x;
	raydir.y = vecset.dir.y + k * vecset.plane.y;

	// printf("lx: %f\n", lx);
	// printf("ly: %f\n", ly);

	distance = get_distance_to_the_wall(vars, raydir);
	printf("distance: %f\n", distance);
	line_height = 0;
	if (distance)
		line_height = WINDOW_HEIGHT / distance;
	printf("line_height: %f\n", line_height);
	return (line_height);
}