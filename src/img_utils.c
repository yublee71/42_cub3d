/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:29:11 by yublee            #+#    #+#             */
/*   Updated: 2025/02/04 15:00:32 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



// t_img	new_file_img(char *file_name, t_vars vars)
// {
// 	t_img	image;

// 	image.img_ptr = mlx_xpm_file_to_image(vars.mlx, file_name,
// 			&image.width, &image.height);
// 	if (!image.img_ptr)
// 		exit_with_error("Image file open\n", EXIT_FAILURE);
// 	else
// 		image.img_pixels_ptr = mlx_get_data_addr(image.img_ptr,
// 				&(image.bits_per_pixel), &(image.size_line), &(image.endian));
// 	return (image);
// }

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

// unsigned int	get_pixel_img(t_img img, int x, int y)
// {
// 	return (*(unsigned int *)((img.img_pixels_ptr
// 			+ (y * img.size_line) + (x * img.bits_per_pixel / 8))));
// }

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

void	draw_image(t_img dst)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_WIDTH / 3)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			put_pixel_img(dst, i, j, (int)0xFF00FFFF);
			j++;
		}
		i++;
	}
	while (i < WINDOW_WIDTH / 3 * 2)
	{
		j = WINDOW_HEIGHT / 3;
		while (j < WINDOW_HEIGHT)
		{
			put_pixel_img(dst, i, j, (int)0xFFFF00FF);
			j++;
		}
		i++;
	}
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			put_pixel_img(dst, i, j, (int)0xFFFFFF00);
			j++;
		}
		i++;
	}
}



