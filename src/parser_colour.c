/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_colour.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:06:58 by mayeung           #+#    #+#             */
/*   Updated: 2025/05/20 15:50:23 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	*type = YES;
	parse->num_texture_colour++;
	return (OK);
}
