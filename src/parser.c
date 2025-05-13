/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:25:43 by mayeung           #+#    #+#             */
/*   Updated: 2025/05/13 20:56:34 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_remove_space(char *line)
{
	while (line && ft_isspace(*line))
		++line;
	return (line);
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
	line = remove_newline_char(parser_get_next_line(fd));
	while (line && !is_err)
	{
		if (need_more_texture_colour(parse))
			is_err = texture_colour_handler(parse, line);
		else
			is_err = map_line_handler(parse, line);
		free(line);
		line = remove_newline_char(parser_get_next_line(fd));
	}
	if (is_err)
		return (free(line), ERR);
	return (OK);
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

int	vars_parser(t_vars *vars, char *path)
{
	int		fd;
	int		is_err;
	t_parse	parse;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (err_msg("Error\nCan't open file\n", ERR));
	ft_bzero(&parse, sizeof(t_parse));
	parse.vars = vars;
	is_err = read_line_from_fd(&parse, fd);
	close(fd);
	if (is_err)
		return (ft_lstclear(&parse.map, free_content),
			err_msg("Error\nParse error\n", ERR));
	if (copy_to_map(&parse))
		return (ft_lstclear(&parse.map, free_content), ERR);
	ft_lstclear(&parse.map, empty_function);
	if (not_enough_data(&parse))
		return (err_msg("Error\nNot enough info\n", ERR));
	*(vars->vecset) = get_vecset(vars->vecset->pos.x,
			vars->vecset->pos.y, parse.facing);
	if (map_not_closed(vars))
		return (err_msg("Error\nMap not closed\n", ERR));
	revert_map(vars);
	return (OK);
}
