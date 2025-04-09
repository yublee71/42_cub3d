/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:31:59 by yublee            #+#    #+#             */
/*   Updated: 2025/04/09 13:03:17 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	initialize_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (err_msg(STR_ERR_MLX_INIT, -1));
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "CUB3D");
	if (!vars->win)
		return (err_msg(STR_ERR_WINDOW_INIT, -1));
	return (0);
}

static int	initialize_image(t_vars *vars)
{
	t_img	image;

	image.img_ptr = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!image.img_ptr)
		return (err_msg(STR_ERR_IMG_INIT, -1));
	image.img_pixels_ptr = mlx_get_data_addr(image.img_ptr,
			&(image.bits_per_pixel), &(image.size_line), &(image.endian));
	if (!image.img_pixels_ptr)
		return (err_msg(STR_ERR_IMG_INIT, -1));
	image.width = WINDOW_WIDTH;
	image.height = WINDOW_HEIGHT;
	vars->img = image;
	return (0);
}

static int	get_img_from_file(char *file_name, t_vars *vars, t_img *img)
{
	t_img	image;

	image.img_ptr = mlx_xpm_file_to_image(vars->mlx, file_name,
			&image.width, &image.height);
	if (!image.img_ptr)
		return (err_msg(STR_ERR_IMG_OPEN, -1));
	image.img_pixels_ptr = mlx_get_data_addr(image.img_ptr,
			&(image.bits_per_pixel), &(image.size_line), &(image.endian));
	if (!image.img_pixels_ptr)
		return (err_msg(STR_ERR_IMG_OPEN, -1));
	*img = image;
	return (0);
}

static int	initialize_assets(t_vars *vars)
{
	if (get_img_from_file(PATH_TO_IMAGE_N, vars, &vars->assets[NORTH]) < 0
		|| get_img_from_file(PATH_TO_IMAGE_S, vars, &vars->assets[SOUTH]) < 0
		|| get_img_from_file(PATH_TO_IMAGE_E, vars, &vars->assets[EAST]) < 0
		|| get_img_from_file(PATH_TO_IMAGE_W, vars, &vars->assets[WEST]) < 0)
		return (-1);
	return (0);
}

void	initialize_cub3d(t_vars *vars)
{
	int	i;

	vars->mlx = NULL;
	vars->win = NULL;
	vars->img.img_ptr = NULL;
	vars->img.img_pixels_ptr = NULL;
	vars->exit_no = EXIT_SUCCESS;
	i = 0;
	while (i < 4)
	{
		vars->assets[i].img_ptr = NULL;
		vars->assets[i].img_pixels_ptr = NULL;
		i++;
	}
	if (initialize_window(vars) < 0
		|| initialize_image(vars) < 0
		|| initialize_assets(vars) < 0)
	{
		vars->exit_no = EXIT_FAILURE;
		close_game(vars);
	}
	return ;
}
