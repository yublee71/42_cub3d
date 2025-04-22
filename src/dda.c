/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:48:23 by yublee            #+#    #+#             */
/*   Updated: 2025/04/22 16:00:00 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_lineinfo	calculate_by_dda(t_vars *vars, t_vec raydir)
{
	t_vecset	vecset;
	t_grid		sign;
	t_distinfo	distance_x;
	t_distinfo	distance_y;
	t_lineinfo	line_info;

	vecset = *vars->vecset;
	sign.x = raydir.x / fabs(raydir.x);
	sign.y = raydir.y / fabs(raydir.y);
	distance_x = get_dist_info_x(vars, vecset, raydir, sign);
	distance_y = get_dist_info_y(vars, vecset, raydir, sign);
	line_info.distance_info = choose_dist(distance_x, distance_y, raydir);
	line_info.line_height = 0;
	if (line_info.distance_info.distance_to_wall)
		line_info.line_height
			= WINDOW_HEIGHT / line_info.distance_info.distance_to_wall;
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
