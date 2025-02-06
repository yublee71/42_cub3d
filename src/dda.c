/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:48:23 by yublee            #+#    #+#             */
/*   Updated: 2025/02/06 16:38:43 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// raypos = pos + l * raydir
double	get_distance_to_the_wall(t_vars *vars, t_vec raydir)
{
	int			raydir_x_sign;
	int			raydir_y_sign;
	double		tan_val;
	double		dx;
	double		dy;
	double		lx;
	double		ly;
	t_grid		pos_grid;
	t_vec		raypos;
	t_grid		raygrid;
	int			i;
	int			j;

	raydir_x_sign = 1;
	raydir_y_sign = 1;
	if (raydir.x < 0)
		raydir_x_sign = -1;
	if (raydir.y < 0)
		raydir_y_sign = -1;

	tan_val = fabs(raydir.y / raydir.x);

	pos_grid.x = (int)(vars->vecset.pos.x);
	pos_grid.y = (int)(vars->vecset.pos.y);

	dx = 1 / tan_val;
	dy = tan_val;

	if (raydir_x_sign > 0)
	{
		i = 1;
		raygrid.x = pos_grid.x + i;
		raypos.y = (int)(vars->vecset.pos.y + l)
	}
	else
	{

	}
	if (raydir_y_sign > 0)
	else
}


// raydir = dir + k * plane
int	calculate_line_height(int i, t_vars *vars)
{
	t_vecset	vecset;
	t_vec		raydir;
	double		k;
	double		distance;
	// double		line_height;

	vecset = vars->vecset;

	k = 2 * (double)i / (double)WINDOW_WIDTH - 1;
	printf("k: %f\n", k);

	raydir.x = vecset.dir.x + k * vecset.plane.x;
	raydir.y = vecset.dir.y + k * vecset.plane.y;

	

	
	
	// printf("lx: %f\n", lx);
	// printf("ly: %f\n", ly);

	distance = get_distance_to_the_wall(vars, raydir);
	// line_height = WINDOW_HEIGHT / distance;

	// printf("%f\n", line_height);
	return (0);
}