/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:25:43 by mayeung           #+#    #+#             */
/*   Updated: 2025/04/19 12:40:06 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <fcntl.h>
#include <limits.h>
#define YES 1
#define NO 0
#define ERR 1
#define OK 0

typedef struct s_parse
{
	int			num_texture_colour;
	int			dir[4];
	int			ceiling;
	int			floor;
	t_cardinal	facing;
	t_list		*map;
	t_vars		*vars;
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

int	is_direction_or_floor_ceiling_identifier(char *line, size_t size)
{
	return (is_dir_elem_identifier(line, size)
		|| is_floor_ceiling_identifier(line, size));
}

int	read_colour(char **to_process, int *colour, int need_comma)
{
	size_t	i;
	int		val;
	char	*line;

	if (!to_process || !*to_process || !colour)
		return (ERR);
	line = *to_process;
	i = 0;
	line = ft_remove_space(line);
	while (line && line[i] && ft_isdigit(line[i]))
		++i;
	if (i > 3 || i == 0 || (need_comma && line[i] != ','))
		return (ERR);
	val = ft_atoi(line);
	if (val > 255 || val < 0)
		return (ERR);
	*colour <<= 8;
	*colour += val;
	*to_process = line + i + need_comma;
	return (OK);
}

int	colour_handler(t_parse *parse, char *line, int *colour, int *type)
{
	if (!parse || !line || !colour || !type)
		return (ERR);
	if (read_colour(&line, colour, YES))
		return (ERR);
	if (read_colour(&line, colour, YES))
		return (ERR);
	if (read_colour(&line, colour, NO))
		return (ERR);
	line = ft_remove_space(line);
	if (*line != '\0')
		return (ERR);
	parse->num_texture_colour++;
	return (OK);
}

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
		return (free(path), ERR);
	free(path);
	line = ft_remove_space(line + i);
	if (*line != '\0')
		return (ERR);
	parse->dir[type]++;
	parse->num_texture_colour++;
	return (OK);
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

int	multiple_start_pos(t_parse *parse)
{
	if (parse->vars->vecset->pos.x != -1 || parse->vars->vecset->pos.y != -1)
		return (YES);
	return (NO);
}

int	set_start_pos_not_ok(t_parse *parse, char facing, size_t i)
{
	if (!parse)
		return (ERR);
	if (multiple_start_pos(parse))
		return (ERR);
	parse->vars->vecset->pos.x = i + 0.5;
	parse->vars->vecset->pos.y = parse->vars->map_height + 0.5;
	if (facing == 'N')
		parse->facing = NORTH;
	if (facing == 'S')
		parse->facing = SOUTH;
	if (facing == 'E')
		parse->facing = EAST;
	if (facing == 'W')
		parse->facing = WEST;
	return (OK);
}

int	contain_invalid_map_char_update_vec_if_need(t_parse *parse, char *line)
{
	size_t	i;

	i = 0;
	if (!parse || !line)
		return (ERR);
	while (line[i])
	{
		if (!ft_strchr("10NSEW ", line[i]))
			return (ERR);
		if (ft_strchr("NSEW", line[i])
			&& set_start_pos_not_ok(parse, line[i], i))
			return (ERR);
		++i;
	}
	return (OK);
}

int	map_line_handler(t_parse *parse, char *line)
{
	t_list	*new;

	if (contain_invalid_map_char_update_vec_if_need(parse, line))
		return (ERR);
	if (!parse->vars->map_height && !ft_strlen(ft_remove_space(line)))
		return (OK);
	parse->vars->map_height++;
	if (ft_strlen(line) > (size_t)parse->vars->map_width)
		parse->vars->map_width = ft_strlen(line);
	if (parse->vars->map_height == INT_MAX || parse->vars->map_width == INT_MAX)
		return (ERR);
	new = ft_lstnew(ft_strdup(line));
	if (!new)
		return (ERR);
	ft_lstadd_back(&parse->map, new);
	return (OK);
}

char	*remove_newline_char(char *line)
{
	if (line && ft_strchr(line, '\n'))
		*(ft_strchr(line, '\n')) = '\0';
	return (line);
}

int	read_line_from_fd(t_parse *parse, int fd)
{
	char	*line;
	int		is_err;

	is_err = NO;
	line = remove_newline_char(get_next_line(fd));
	while (line && !is_err)
	{
		if (need_more_texture_colour(parse))
			is_err = texture_colour_handler(parse, line);
		else
			is_err = map_line_handler(parse, line);
		free(line);
		line = remove_newline_char(get_next_line(fd));
	}
	if (is_err)
		return (free(line), ERR);
	return (OK);
}

int	copy_to_map(t_parse *parse)
{
	size_t	i;
	t_list	*node;

	if (!parse)
		return (ERR);
	parse->vars->map = ft_calloc((ft_lstsize(parse->map) + 1), sizeof(char *));
	if (!parse->vars->map)
		return (ERR);
	i = 0;
	node = parse->map;
	while (node)
	{
		parse->vars->map[i++] = node->content;
		node = node->next;
	}
	return (OK);
}

void	empty_function(void *arg)
{
	(void)arg;
}

int	not_enough_data(t_parse *parse)
{
	if (!parse)
		return (ERR);
	if (parse->num_texture_colour != 6)
		return (ERR);
	if (!parse->vars->map)
		return (ERR);
	if (parse->vars->vecset->pos.x == -1 || parse->vars->vecset->pos.y == -1)
		return (ERR);
	return (OK);
}

int	partition_not_closed(t_vars *vars, int i, int j)
{
	if (!vars
		|| i == -1
		|| j == -1
		|| j >= vars->map_height
		|| i >= (int)ft_strlen(vars->map[j])
		|| vars->map[j][i] == ' ')
		return (ERR);
	if (vars->map[j][i] == '1' || vars->map[j][i] == 'D')
		return (OK);
	vars->map[j][i] = 'D';
	return (partition_not_closed(vars, i + 1, j)
		|| partition_not_closed(vars, i - 1, j)
		|| partition_not_closed(vars, i, j + 1)
		|| partition_not_closed(vars, i, j - 1));
}

int	map_not_closed(t_vars *vars)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < (size_t)vars->map_height)
	{
		i = 0;
		while (i < ft_strlen(vars->map[j]))
		{
			if (ft_strchr("NSEW0", vars->map[j][i])
				&& partition_not_closed(vars, i, j))
				return (ERR);
			++i;
		}
		++j;
	}
	return (OK);
}

void	revert_map(t_vars *vars)
{
	size_t	i;
	size_t	j;

	if (!vars)
		return ;
	j = 0;
	while (j < (size_t)vars->map_height)
	{
		i = 0;
		while (i < ft_strlen(vars->map[j]))
		{
			if (vars->map[j][i] == 'D')
				vars->map[j][i] = '0';
			++i;
		}
		++j;
	}
}

int	vars_parser(t_vars *vars, char *path)
{
	int		fd;
	int		is_err;
	t_parse	parse;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Can't open file\n", STDERR_FILENO), ERR);
	ft_bzero(&parse, sizeof(t_parse));
	parse.vars = vars;
	is_err = read_line_from_fd(&parse, fd);
	close(fd);
	if (is_err)
		return (ft_lstclear(&parse.map, empty_function),
			ft_putstr_fd("Parse error\n", STDERR_FILENO), ERR);
	if (copy_to_map(&parse))
		return (ft_lstclear(&parse.map, empty_function), ERR);
	ft_lstclear(&parse.map, empty_function);
	if (not_enough_data(&parse))
		return (ft_putstr_fd("Not enough info\n", STDERR_FILENO), ERR);
	*(vars->vecset) = get_vecset(vars->vecset->pos.x,
			vars->vecset->pos.y, parse.facing);
	if (map_not_closed(vars))
		return (ft_putstr_fd("Map not closed\n", STDERR_FILENO), ERR);
	revert_map(vars);
	return (OK);
}
