/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:11:34 by mayeung           #+#    #+#             */
/*   Updated: 2025/05/13 20:55:58 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	load_texture_to_img(t_parse *parse, char *path, t_img *img)
{
	if (!parse || !path)
		return (err_msg(STR_ERR_IMG_OPEN, ERR));
	img->img_ptr = mlx_xpm_file_to_image(parse->vars->mlx,
			path, &img->width, &img->height);
	if (!img->img_ptr)
		return (err_msg(STR_ERR_IMG_OPEN, ERR));
	img->img_pixels_ptr = mlx_get_data_addr(img->img_ptr,
			&img->bits_per_pixel, &img->size_line, &img->endian);
	if (!img->img_pixels_ptr)
		return (err_msg(STR_ERR_IMG_OPEN, ERR));
	return (OK);
}

int	texture_handler(t_parse *parse, char *line, int type)
{
	size_t	i;
	char	*path;

	i = 0;
	line = ft_remove_space(line);
	while (line && line[i] && !ft_isspace(line[i]))
		++i;
	path = ft_substr(line, 0, i);
	if (!path)
		return (ERR);
	if (load_texture_to_img(parse, path, &parse->vars->assets[type]))
		return (free(path), err_msg("Error\nCan't open texture file\n", ERR));
	free(path);
	line = ft_remove_space(line + i);
	if (*line != '\0')
		return (ERR);
	parse->dir[type]++;
	parse->num_texture_colour++;
	return (OK);
}
