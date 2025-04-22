/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:41:01 by mayeung           #+#    #+#             */
/*   Updated: 2025/04/22 15:42:28 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
