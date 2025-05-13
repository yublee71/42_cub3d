/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:20:10 by mayeung           #+#    #+#             */
/*   Updated: 2025/05/13 17:35:49 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	if (!(ft_strlen(ft_remove_space(line))))
		return (ERR);
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
