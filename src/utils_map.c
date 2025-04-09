/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:48:47 by yublee            #+#    #+#             */
/*   Updated: 2025/04/09 14:54:24 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	isinthemap(t_vars *vars, t_grid grid)
{
	if (grid.x >= 0 && grid.x < vars->map_width
		&& grid.y >= 0 && grid.y < vars->map_height)
		return (1);
	return (0);
}
