/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:59:36 by yublee            #+#    #+#             */
/*   Updated: 2025/05/20 15:56:04 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	put_pixel_to_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xff000000)
		return ;
	if (x >= 0 && y >= 0 && x < img.width && y < img.height)
	{
		dst = img.img_pixels_ptr
			+ (y * img.size_line + x * (img.bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

static unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.img_pixels_ptr
			+ (y * img.size_line) + (x * img.bits_per_pixel / 8))));
}

static void	put_asset_to_img(t_vars *vars, t_lineinfo line_info, int x, int y)
{
	t_img	dst;
	t_img	src;
	double	scale_y;
	double	j;
	double	k;

	dst = vars->img;
	src = vars->assets[line_info.distance_info.hit_direction];
	scale_y = (double)line_info.line_height
		/ vars->assets[line_info.distance_info.hit_direction].height;
	k = 0;
	j = 0;
	if (src.height * scale_y > WINDOW_HEIGHT)
		j = (src.height * scale_y - WINDOW_HEIGHT) / 2;
	while (j < src.height * scale_y && y + k < WINDOW_HEIGHT)
	{
		put_pixel_to_img(dst, x, y + k,
			get_pixel_img(src, src.width
				* line_info.distance_info.distance_to_grid, j / scale_y));
		j++;
		k++;
	}
}

static void	draw_line(int i, t_vars *vars, t_lineinfo line_info)
{
	int	ceiling_height;
	int	j;

	ceiling_height = (WINDOW_HEIGHT - line_info.line_height) / 2;
	j = 0;
	while (j < ceiling_height)
	{
		put_pixel_to_img(vars->img, i, j, vars->colorset.color_ceiling);
		j++;
	}
	put_asset_to_img(vars, line_info, i, j);
	j += line_info.line_height;
	while (j < WINDOW_HEIGHT)
	{
		put_pixel_to_img(vars->img, i, j, vars->colorset.color_floor);
		j++;
	}
}

void	draw_image(t_vars *vars)
{
	t_lineinfo	line_info;
	int			i;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		line_info = get_line_info_by_dda(i, vars);
		draw_line(i, vars, line_info);
		i++;
	}
}
