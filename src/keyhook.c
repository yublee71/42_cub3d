/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:59:25 by yublee            #+#    #+#             */
/*   Updated: 2025/02/12 18:44:34 by yublee           ###   ########.fr       */
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

static void	move_player(t_vars *vars, int direction)
{
	t_vec	new_pos;
	t_grid	new_grid;

	new_pos.x = vars->vecset->pos.x + vars->vecset->dir.x * direction;
	new_pos.y = vars->vecset->pos.y + vars->vecset->dir.y * direction;
	new_grid.x = (int)new_pos.x;
	new_grid.y = (int)new_pos.y;
	if (isinthemap(vars, new_grid))
	{
		vars->vecset->pos = new_pos;
		draw_image(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img_ptr, 0, 0);
	}
}

int	handle_key_input(int keysym, t_vars *vars)
{
	if (keysym == XK_Escape)
		close_game(vars);
	else if (keysym == XK_d) //TODO: change to wasd
		rotate_vecset(vars, MOVE_ANGLE);
	else if (keysym == XK_a) //TODO: change to wasd
		rotate_vecset(vars, -MOVE_ANGLE);
	else if (keysym == XK_w) //TODO: change to wasd
		move_player(vars, PLUS);
	else if (keysym == XK_s) //TODO: change to wasd
		move_player(vars, MINUS);
	return (0);
}
