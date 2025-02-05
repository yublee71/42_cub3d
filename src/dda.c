/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:48:23 by yublee            #+#    #+#             */
/*   Updated: 2025/02/05 21:01:51 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// raydir = dir + k * plane
int	calculate_line_height(int i, t_vars *vars)
{
	t_vecset	vecset;
	t_vec		raydir;
	t_grid		pos_grid;
	// t_grid		firstwall_grid;
	double		k;
	double		tan_val;
	double		dx;
	double		dy;
	// double		lx;
	// double		ly;
	// double		distance;
	// double		line_height;

	vecset = vars->vecset;

	k = 2 * (double)i / (double)WINDOW_WIDTH - 1;
	printf("k: %f\n", k);

	raydir.x = vecset.dir.x + k * vecset.plane.x;
	raydir.y = vecset.dir.y + k * vecset.plane.y;

	tan_val = fabs(raydir.y / raydir.x);

	pos_grid.x = (int)vecset.pos.x;
	pos_grid.y = (int)vecset.pos.y;

	
	
	// printf("lx: %f\n", lx);
	// printf("ly: %f\n", ly);

	// distance = check_wall_hit(vars, raydir, lx, ly, firstwall_grid);
	// line_height = WINDOW_HEIGHT / distance;

	// printf("%f\n", line_height);
	return (0);
}