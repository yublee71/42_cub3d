/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_cases.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:32:00 by yublee            #+#    #+#             */
/*   Updated: 2025/02/07 17:47:57y yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	isinthemap(t_vars *vars, t_grid grid)
{
	if (grid.x >= 0 && grid.x < vars->map_width
		&& grid.y >= 0 && grid.y < vars->map_height)
		return (1);
	return 0;
}

static double	compare_distances(double distance_x, double distance_y)
{
	double	distance;

	distance = 0;
	if (distance_x && distance_y)
	{
		if (distance_x < distance_y)
			distance = distance_x;
		else
			distance = distance_y;
	}
	else
	{
		if (distance_x)
			distance = distance_x;
		else if (distance_y)
			distance = distance_y;
	}
	return distance;
}

//x>0 y>0
double	get_distance_to_the_wall_case1(t_vars *vars, double raydir_tan)
{
	double		distance_x;
	double		distance_y;
	double		distance;
	t_vec		firstwall_pos;
	t_grid		firstwall_grid;
	t_vecset	vecset;
	double		dx;
	double		dy;

	vecset = *vars->vecset;
	distance_x = 0;
	distance_y = 0;

	firstwall_pos.x = (int)vecset.pos.x + 1;
	dx = firstwall_pos.x - vecset.pos.x;
	firstwall_pos.y = vecset.pos.y + dx * raydir_tan;
	firstwall_grid.x = (int)firstwall_pos.x;
	firstwall_grid.y = (int)firstwall_pos.y;
	
	while (isinthemap(vars, firstwall_grid))
	{
		if (vars->map[firstwall_grid.y][firstwall_grid.x] == '1')
		{
			// printf("x encounter: x: %d y: %d\n", firstwall_grid.x, firstwall_grid.y);
			distance_x = get_vector_to_vector_distance(vecset.pos, firstwall_pos);
			break ;
		}
		firstwall_pos.x++;
		firstwall_pos.y += raydir_tan;
		firstwall_grid.x = (int)firstwall_pos.x;
		firstwall_grid.y = (int)firstwall_pos.y;
	}
	
	firstwall_pos.y = (int)vecset.pos.y + 1;
	dy = firstwall_pos.y - vecset.pos.y;
	firstwall_pos.x = vecset.pos.x + dy / raydir_tan;
	firstwall_grid.x = (int)firstwall_pos.x;
	firstwall_grid.y = (int)firstwall_pos.y;
	
	while (isinthemap(vars, firstwall_grid))
	{
		if (vars->map[firstwall_grid.y][firstwall_grid.x] == '1')
		{
			// printf("y encounter: x: %d y: %d\n", firstwall_grid.x, firstwall_grid.y);
			distance_y = get_vector_to_vector_distance(vecset.pos, firstwall_pos);
			// printf("distance_y: %f\n", distance_y);
			break ;
		}
		firstwall_pos.y++;
		firstwall_pos.x += 1 / raydir_tan;
		firstwall_grid.x = (int)firstwall_pos.x;
		firstwall_grid.y = (int)firstwall_pos.y;
	}
	distance = compare_distances(distance_x, distance_y);

	return (distance);
}

//x>0 y<0
double	get_distance_to_the_wall_case2(t_vars *vars, double raydir_tan)
{
	double		distance_x;
	double		distance_y;
	double		distance;
	t_vec		firstwall_pos;
	t_grid		firstwall_grid;
	t_vecset	vecset;
	double		dx;
	double		dy;

	vecset = *vars->vecset;
	distance_x = 0;
	distance_y = 0;

	firstwall_pos.x = (int)vecset.pos.x + 1;
	dx = firstwall_pos.x - vecset.pos.x;
	firstwall_pos.y = vecset.pos.y - dx * raydir_tan;
	firstwall_grid.x = (int)firstwall_pos.x;
	firstwall_grid.y = (int)firstwall_pos.y;
	
	while (isinthemap(vars, firstwall_grid))
	{
		if (vars->map[firstwall_grid.y][firstwall_grid.x] == '1')
		{
			// printf("x encounter: x: %d y: %d\n", firstwall_grid.x, firstwall_grid.y);
			distance_x = get_vector_to_vector_distance(vecset.pos, firstwall_pos);
			break ;
		}
		firstwall_pos.x++;
		firstwall_pos.y -= raydir_tan;
		firstwall_grid.x = (int)firstwall_pos.x;
		firstwall_grid.y = (int)firstwall_pos.y;
	}
	
	firstwall_pos.y = (int)vecset.pos.y;
	dy = vecset.pos.y - firstwall_pos.y;
	firstwall_pos.x = vecset.pos.x + dy / raydir_tan;
	firstwall_grid.x = (int)firstwall_pos.x - 1;
	firstwall_grid.y = (int)firstwall_pos.y;
	
	while (isinthemap(vars, firstwall_grid))
	{
		if (vars->map[firstwall_grid.y][firstwall_grid.x] == '1')
		{
			// printf("y encounter: x: %d y: %d\n", firstwall_grid.x, firstwall_grid.y);
			distance_y = get_vector_to_vector_distance(vecset.pos, firstwall_pos);
			// printf("distance_y: %f\n", distance_y);
			break ;
		}
		firstwall_pos.y--;
		firstwall_pos.x += 1 / raydir_tan;
		firstwall_grid.x = (int)firstwall_pos.x;
		firstwall_grid.y = (int)firstwall_pos.y - 1;
	}
	distance = compare_distances(distance_x, distance_y);

	return (distance);
}

//x<0 y>0
double	get_distance_to_the_wall_case3(t_vars *vars, double raydir_tan)
{
	double		distance_x;
	double		distance_y;
	double		distance;
	t_vec		firstwall_pos;
	t_grid		firstwall_grid;
	t_vecset	vecset;
	double		dx;
	double		dy;

	vecset = *vars->vecset;
	distance_x = 0;
	distance_y = 0;

	firstwall_pos.x = (int)vecset.pos.x;
	dx = vecset.pos.x - firstwall_pos.x;
	firstwall_pos.y = vecset.pos.y + dx * raydir_tan;
	firstwall_grid.x = (int)firstwall_pos.x - 1;
	firstwall_grid.y = (int)firstwall_pos.y;
	
	while (isinthemap(vars, firstwall_grid))
	{
		if (vars->map[firstwall_grid.y][firstwall_grid.x] == '1')
		{
			// printf("x encounter: x: %d y: %d\n", firstwall_grid.x, firstwall_grid.y);
			distance_x = get_vector_to_vector_distance(vecset.pos, firstwall_pos);
			break ;
		}
		firstwall_pos.x--;
		firstwall_pos.y += raydir_tan;
		firstwall_grid.x = (int)firstwall_pos.x - 1;
		firstwall_grid.y = (int)firstwall_pos.y;
	}
	
	firstwall_pos.y = (int)vecset.pos.y + 1;
	dy = firstwall_pos.y - vecset.pos.y;
	firstwall_pos.x = vecset.pos.x - dy / raydir_tan;
	firstwall_grid.x = (int)firstwall_pos.x;
	firstwall_grid.y = (int)firstwall_pos.y;
	
	while (isinthemap(vars, firstwall_grid))
	{
		if (vars->map[firstwall_grid.y][firstwall_grid.x] == '1')
		{
			// printf("y encounter: x: %d y: %d\n", firstwall_grid.x, firstwall_grid.y);
			distance_y = get_vector_to_vector_distance(vecset.pos, firstwall_pos);
			// printf("distance_y: %f\n", distance_y);
			break ;
		}
		firstwall_pos.y++;
		firstwall_pos.x -= 1 / raydir_tan;
		firstwall_grid.x = (int)firstwall_pos.x;
		firstwall_grid.y = (int)firstwall_pos.y;
	}

	distance = compare_distances(distance_x, distance_y);
	return (distance);
}

//x<0 y<0
double	get_distance_to_the_wall_case4(t_vars *vars, double raydir_tan)
{
	double		distance_x;
	double		distance_y;
	double		distance;
	t_vec		firstwall_pos;
	t_grid		firstwall_grid;
	t_vecset	vecset;
	double		dx;
	double		dy;

	vecset = *vars->vecset;
	distance_x = 0;
	distance_y = 0;

	firstwall_pos.x = (int)vecset.pos.x;
	dx = vecset.pos.x - firstwall_pos.x;
	firstwall_pos.y = vecset.pos.y - dx * raydir_tan;
	firstwall_grid.x = (int)firstwall_pos.x - 1;
	firstwall_grid.y = (int)firstwall_pos.y;
	
	while (isinthemap(vars, firstwall_grid))
	{
		if (vars->map[firstwall_grid.y][firstwall_grid.x] == '1')
		{
			// printf("x encounter: x: %d y: %d\n", firstwall_grid.x, firstwall_grid.y);
			distance_x = get_vector_to_vector_distance(vecset.pos, firstwall_pos);
			break ;
		}
		firstwall_pos.x--;
		firstwall_pos.y -= raydir_tan;
		firstwall_grid.x = (int)firstwall_pos.x - 1;
		firstwall_grid.y = (int)firstwall_pos.y;
	}
	
	firstwall_pos.y = (int)vecset.pos.y;
	dy = vecset.pos.y - firstwall_pos.y;
	firstwall_pos.x = vecset.pos.x - dy / raydir_tan;
	firstwall_grid.x = (int)firstwall_pos.x;
	firstwall_grid.y = (int)firstwall_pos.y - 1;
	
	while (isinthemap(vars, firstwall_grid))
	{
		if (vars->map[firstwall_grid.y][firstwall_grid.x] == '1')
		{
			// printf("y encounter: x: %d y: %d\n", firstwall_grid.x, firstwall_grid.y);
			distance_y = get_vector_to_vector_distance(vecset.pos, firstwall_pos);
			// printf("distance_y: %f\n", distance_y);
			break ;
		}
		firstwall_pos.y--;
		firstwall_pos.x -= 1 / raydir_tan;
		firstwall_grid.x = (int)firstwall_pos.x;
		firstwall_grid.y = (int)firstwall_pos.y - 1;
	}

	distance = compare_distances(distance_x, distance_y);
	return (distance);
}