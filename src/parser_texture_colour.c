/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture_colour.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:21:49 by mayeung           #+#    #+#             */
/*   Updated: 2025/04/22 16:22:24 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	need_more_texture_colour(t_parse *parse)
{
	if (parse && parse->num_texture_colour < 6)
		return (YES);
	return (NO);
}

int	is_dir_elem_identifier(char *line, size_t size)
{
	return (size == 2
		&& (!ft_strncmp(line, "NO", size)
			|| !ft_strncmp(line, "SO", size)
			|| !ft_strncmp(line, "EA", size)
			|| !ft_strncmp(line, "WE", size)));
}

int	is_floor_ceiling_identifier(char *line, size_t size)
{
	return (size == 1
		&& (!ft_strncmp(line, "F", size)
			|| !ft_strncmp(line, "C", size)));
}

int	is_direction_or_floor_ceiling_identifier(char *line, size_t size)
{
	return (is_dir_elem_identifier(line, size)
		|| is_floor_ceiling_identifier(line, size));
}

int	texture_colour_handler(t_parse *parse, char *line)
{
	size_t	i;

	i = 0;
	line = ft_remove_space(line);
	if (!*line)
		return (OK);
	while (line[i] && !ft_isspace(line[i]))
		++i;
	if (!is_direction_or_floor_ceiling_identifier(line, i))
		return (ERR);
	if (!ft_strncmp(line, "NO", i) && !parse->dir[NORTH])
		return (texture_handler(parse, line + i, NORTH));
	if (!ft_strncmp(line, "SO", i) && !parse->dir[SOUTH])
		return (texture_handler(parse, line + i, SOUTH));
	if (!ft_strncmp(line, "EA", i) && !parse->dir[EAST])
		return (texture_handler(parse, line + i, EAST));
	if (!ft_strncmp(line, "WE", i) && !parse->dir[WEST])
		return (texture_handler(parse, line + i, WEST));
	if (!ft_strncmp(line, "C", i) && !parse->ceiling)
		return (colour_handler(parse, line + i,
				&parse->vars->colorset.color_ceiling, &parse->ceiling));
	if (!ft_strncmp(line, "F", i) && !parse->floor)
		return (colour_handler(parse, line + i,
				&parse->vars->colorset.color_floor, &parse->floor));
	return (ERR);
}
