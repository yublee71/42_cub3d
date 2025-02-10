/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:59:36 by yublee            #+#    #+#             */
/*   Updated: 2025/02/10 16:18:30 by yublee           ###   ########.fr       */
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
	t_lineinfo	line_info;
	int			i;
	int			line_color;
	int			colors[4];

	i = 0;
/* this section will be removed later */
	colors[0] = (int)0xffe62012; //NORTH red
	colors[1] = (int)0xffe64e12; //SOUTH orange
	colors[2] = (int)0xffe6d412; //EAST yellow
	colors[3] = (int)0xff12e616; //WEST green
/* ********************************** */
	while (i < WINDOW_WIDTH)
	{
		line_info = calculate_line_height(i, vars);
		line_color = colors[line_info.hit_direction];
		draw_line(i, vars, line_info.line_height, line_color);
		i++;
	}
}