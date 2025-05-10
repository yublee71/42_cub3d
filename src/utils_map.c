/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:48:47 by yublee            #+#    #+#             */
/*   Updated: 2025/05/10 20:03:57 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	isinthemap(t_vars *vars, t_grid grid)
{
	if (grid.y >= 0 && grid.y < vars->map_height
		&& grid.x >= 0 && grid.x < (int)ft_strlen(vars->map[grid.y])
		&& vars->map[grid.y][grid.x] != ' ')
		return (1);
	return (0);
}
