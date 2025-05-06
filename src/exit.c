/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:17:35 by yublee            #+#    #+#             */
/*   Updated: 2025/05/06 16:30:43 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	err_msg(char *msg, int return_val)
{
	printf("%s", msg);
	return (return_val);
}

int	close_game(t_vars *vars)
{
	int	i;

	if (vars->mlx)
	{
		if (vars->win)
			mlx_destroy_window(vars->mlx, vars->win);
		if (vars->img.img_ptr)
			mlx_destroy_image(vars->mlx, vars->img.img_ptr);
		i = 0;
		while (i < 4)
		{
			if (vars->assets[i].img_ptr)
				mlx_destroy_image(vars->mlx, vars->assets[i].img_ptr);
			i++;
		}
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		i = 0;
		while (vars->map && vars->map[i])
			free(vars->map[i++]);
		free(vars->map);
	}
	exit(vars->exit_no);
	return (0);
}
