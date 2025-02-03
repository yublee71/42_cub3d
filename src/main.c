/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:46:40 by yublee            #+#    #+#             */
/*   Updated: 2025/02/03 19:26:30 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	initialize_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (err_msg(STR_ERR_MLX_INIT, -1));
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"CUB3D");
	if (!vars->win)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		return (err_msg(STR_ERR_WINDOW_INIT, -1));
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	(void)argc;
	(void)argv;
	if (initialize_window(&vars) < 0)
		return (EXIT_FAILURE);
	mlx_key_hook(vars.win, handle_key_input, &vars);
	mlx_hook(vars.win, 17, 1L << 2, close_game, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
