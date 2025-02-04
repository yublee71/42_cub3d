/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:17:35 by yublee            #+#    #+#             */
/*   Updated: 2025/02/04 16:17:58 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_game(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_image(vars->mlx, vars->img.img_ptr);
	mlx_destroy_image(vars->mlx, vars->assets[0].img_ptr);
	mlx_destroy_image(vars->mlx, vars->assets[1].img_ptr);
	mlx_destroy_image(vars->mlx, vars->assets[2].img_ptr);
	mlx_destroy_image(vars->mlx, vars->assets[3].img_ptr);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}