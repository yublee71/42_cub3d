/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:59:36 by yublee            #+#    #+#             */
/*   Updated: 2025/02/10 14:29:51 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

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

static void	draw_line(int i, t_vars *vars, int line_height, int line_color)
{
	int	ceiling_height;
	int	j;

	ceiling_height = (WINDOW_HEIGHT - line_height) / 2;
	j = 0;
	while (j < ceiling_height)
	{
		put_pixel_img(vars->img, i, j, vars->colorset.color_ceiling);
		j++;
	}
	while (j < ceiling_height + line_height)
	{
		put_pixel_img(vars->img, i, j, line_color);
		j++;
	}
	while (j < WINDOW_HEIGHT)
	{
		put_pixel_img(vars->img, i, j, vars->colorset.color_floor);
		j++;
	}
}

void	draw_image_with_color(t_vars *vars)
{
	int	i;
	int	line_height;
	int	line_color;

	i = 0;
	line_height = WINDOW_HEIGHT;
	line_color = (int)0xffffffff;
	while (i < WINDOW_WIDTH)
	{
		line_height = calculate_line_height(i, vars);
		draw_line(i, vars, line_height, line_color);
		i++;
	}
}