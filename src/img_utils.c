/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:29:11 by yublee            #+#    #+#             */
/*   Updated: 2025/02/04 16:08:29 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_img	get_img_from_file(char *file_name, t_vars vars)
{
	t_img	image;

	image.img_ptr = mlx_xpm_file_to_image(vars.mlx, file_name,
			&image.width, &image.height);
	if (!image.img_ptr)
		exit(EXIT_FAILURE); // TODO
	else
		image.img_pixels_ptr = mlx_get_data_addr(image.img_ptr,
				&(image.bits_per_pixel), &(image.size_line), &(image.endian));
	return (image);
}



