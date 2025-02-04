/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:59:36 by yublee            #+#    #+#             */
/*   Updated: 2025/02/04 17:19:49 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

static void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
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
// void	put_img_to_img(t_img dst, t_img src, int x, int y)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < src.width)
// 	{
// 		j = 0;
// 		while (j < src.height)
// 		{
// 			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
// 			j++;
// 		}
// 		i++;
// 	}
// }
static void	put_img_to_img(t_img dst, t_img src, int x, int y, int scale_x, int scale_y)
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	pixel;
	int	y_origin;

	i = 0;
	y_origin = y;
	while (i < src.width)
	{
		y = y_origin;
		j = 0;
		while (j < src.height)
		{
			pixel = get_pixel_img(src, i, j);
			l = 0;
			while (l < scale_y)
			{
				k = 0;
				while (k < scale_x)
				{
					put_pixel_img(dst, x + k, y + l, pixel);
					k++;
				}
				l++;
			}
			y += scale_y;
			j++;
		}
		x += scale_x;
		i++;
	}
}

// void	draw_image(t_img dst)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < WINDOW_WIDTH / 3)
// 	{
// 		j = 0;
// 		while (j < WINDOW_HEIGHT)
// 		{
// 			put_pixel_img(dst, i, j, (int)0xFFFFFFFF);
// 			j++;
// 		}
// 		i++;
// 	}
// 	while (i < WINDOW_WIDTH / 3 * 2)
// 	{
// 		j = WINDOW_HEIGHT / 3;
// 		while (j < WINDOW_HEIGHT)
// 		{
// 			put_pixel_img(dst, i, j, (int)0xFFFF00FF);
// 			j++;
// 		}
// 		i++;
// 	}
// 	while (i < WINDOW_WIDTH)
// 	{
// 		j = 0;
// 		while (j < WINDOW_HEIGHT)
// 		{
// 			put_pixel_img(dst, i, j, (int)0xFFFFFF00);
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	draw_image(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	put_img_to_img(vars->img, vars->assets[0], i, j, 3, 10);
	i += vars->assets[0].width * 3 + 10;
	put_img_to_img(vars->img, vars->assets[1], i, j, 10, 5);
	i += vars->assets[1].width * 10 + 10;
	put_img_to_img(vars->img, vars->assets[2], i, j, 5, 10);
}