/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:25:43 by mayeung           #+#    #+#             */
/*   Updated: 2025/04/16 01:36:16 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <fcntl.h>
#define YES 1
#define NO 0
#define ERR 1
#define OK 0

typedef struct s_parse
{
	int		num_texture_colour;
	int		dir[4];
	int		ceiling;
	int		floor;
	t_list	*map;
	t_vars	*vars;
}	t_parse;

char	*ft_remove_space(char *line)
{
	while (line && ft_isspace(*line))
		++line;
	return (line);
}

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

int	read_colour(char **to_process, int *colour, int need_comma)
{
	size_t	i;
	int		val;
	char	*line;

	if (!line || !*line || !colour)
		return (ERR);
	line = *to_process;
	i = 0;
	line = ft_remove_space(line);
	while (line && line[i] && ft_isdigit(line[i]))
		++i;
	if (i > 3 || (need_comma && line[i] != ','))
		return (ERR);
	val = ft_atoi(line);
	if (val > 255 || val < 0)
		return (ERR);
	*colour <<= 8;
	*colour += val;
	*to_process = line;
	return (OK);
}

int	colour_handler(t_parse *parse, char *line, int *colour, int *type)
{
	size_t	i;
	int		val;

	if (!parse || !line || !colour || !type)
		return (ERR);
	if (read_colour(&line, colour, YES))
		return (ERR);
	if (read_colour(&line, colour, YES))
		return (ERR);
	if (read_colour(&line, colour, NO))
		return (ERR);
	line = ft_remove_space(line);
	if (*line != '\n' || *line != '\0')
		return (ERR);
	return (OK);
}

int	load_texture_to_img(t_parse *parse, char *path, t_img *img)
{
	if (!parse || !path || !img)
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
		return (free(path), ERR);
	free(path);
	line = ft_remove_space(line + i);
	if (*line != '\n' || *line != '\0')
		return (ERR);
	++(parse->dir[type]);
	return (OK);
}

int	texture_colour_handler(t_parse *parse, char *line)
{
	size_t	i;

	i = 0;
	line = ft_remove_space(line);
	while (line[i] && !ft_isspace(line[i]))
		++i;
	if (!is_dir_elem_identifier(line, i)
		&& !is_floor_ceiling_identifier(line, i))
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
		return (colour_handler(parse, line,
				&parse->vars->colorset.color_ceiling, &parse->ceiling));
	if (!ft_strncmp(line, "F", i) && !parse->floor)
		return (colour_handler(parse, line,
				&parse->vars->colorset.color_floor, &parse->floor));
	return (ERR);
}

int	contain_invalid_map_char(char *line)
{
	if (!line)
		return (ERR);
	while (*line && *line != '\n')
	{
		if (ft_strchr("10NSEW ", *line))
			return (ERR);
		++line;
	}
	return (OK);
}

int	map_line_handler(t_parse *parse, char *line)
{
	size_t	i;

	i = 0;
	if (contain_invalid_map_char(line))
		return (ERR);
	ft_lstadd_back(&parse->map, ft_lstnew(line));
	return (OK);
}

int	read_line_from_fd(t_parse *parse, int fd)
{
	char	*line;
	int		is_err;

	is_err = NO;
	line = get_next_line(fd);
	while (line && !is_err)
	{
		if (need_more_texture_colour(parse))
			is_err = texture_colour_handler(parse, line);
		else
			is_err = map_line_handler(parse, line);
		free(line);
		line = get_next_line(fd);
	}
	if (is_err)
		return (free(line), ERR);
	return (OK);
}

int	vars_parser(t_vars *vars, char *path)
{
	int		fd;
	int		is_err;
	char	*line;
	t_parse	parse;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Can't open file\n", STDERR_FILENO), ERR);
	ft_bzero(&parse, sizeof(t_parse));
	parse.vars = vars;
	is_err = read_line_from_fd(&parse, fd);
	close(fd);
}
