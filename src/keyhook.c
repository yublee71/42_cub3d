/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:59:25 by yublee            #+#    #+#             */
/*   Updated: 2025/02/12 16:50:50 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	rotate_vecset(t_vars *vars, int degree)
{
	t_vec	new_dir;
	t_vec	new_plane;

	new_dir = rotate_vector(vars->vecset->dir, degree);
	new_plane = rotate_vector(vars->vecset->plane, degree);
	vars->vecset->dir = new_dir;
	vars->vecset->plane = new_plane;
	draw_image(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img_ptr, 0, 0);
}

int	handle_key_input(int keysym, t_vars *vars)
{
	if (keysym == XK_Escape)
		close_game(vars);
	else if (keysym == XK_Right) //TODO: change to wasd
		rotate_vecset(vars, MOVE_ANGLE);
	else if (keysym == XK_Left) //TODO: change to wasd
		rotate_vecset(vars, -MOVE_ANGLE);
	return (0);
}
