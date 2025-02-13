/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:52:21 by yublee            #+#    #+#             */
/*   Updated: 2025/02/13 17:21:49 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	get_vector_length(t_vec raydir)
{
	double	length;
	
	length = sqrt(pow(raydir.x, 2) + pow(raydir.y, 2));
	return (length);
}

double	get_line_to_point_distance(double tan, t_vec pos, t_vec dot)
{
	double	distance;

	distance = fabs(tan * dot.x - dot.y - tan * pos.x + pos.y) / sqrt(pow(tan, 2) + 1);
	return (distance);
}

double	convert_deg_to_rad(double degree)
{
	double	radian;

	radian = M_PI / 180 * degree;
	return (radian);
}

t_vec	rotate_vector(t_vec	vec, int degree)
{
	t_vec	rotated_vec;
	double	radian;

	radian = convert_deg_to_rad(degree);
	rotated_vec.x = vec.x * cos(radian) - vec.y * sin(radian);
	rotated_vec.y = vec.x * sin(radian) + vec.y * cos(radian);
	return (rotated_vec);
}
