/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:59:36 by yublee            #+#    #+#             */
/*   Updated: 2025/04/09 14:59:51 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	put_pixel_img(t_img img, int x, int y, int color)
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

static void	put_img_to_img(t_img dst, t_img src, int x, int y, double pos_x, double scale_y)
{
	double	i;
	double	j;
	double	k;
	int		pixel;

	i = src.width * pos_x;
	j = 0;
	k = 0;
	if (src.height * scale_y > WINDOW_HEIGHT)
		k = - (src.height * scale_y - WINDOW_HEIGHT) / 2;
	while (j < src.height * scale_y)
	{
		pixel = get_pixel_img(src, i, j / scale_y);
		if (k >= 0)
		{
			put_pixel_img(dst, x, y + k, pixel);
		}
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
		put_pixel_img(vars->img, i, j, vars->colorset.color_ceiling);
		j++;
	}
	put_img_to_img(vars->img, vars->assets[line_info.distance_info.hit_direction], i, j, line_info.distance_info.distance_to_grid, (double)line_info.line_height / vars->assets[line_info.distance_info.hit_direction].height);
	j += line_info.line_height;
	while (j < WINDOW_HEIGHT)
	{
		put_pixel_img(vars->img, i, j, vars->colorset.color_floor);
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
