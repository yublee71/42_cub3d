/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:52:21 by yublee            #+#    #+#             */
/*   Updated: 2025/02/07 21:41:55 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	get_vector_length(t_vec raydir)
{
	double	length;
	
	length = sqrt(pow(raydir.x, 2) + pow(raydir.y, 2));
	return (length);
}

double	get_vector_to_vector_distance(t_vec vec1, t_vec vec2)
{
	double	distance;
	
	distance = sqrt(pow((vec1.x - vec2.x), 2) + pow((vec1.y - vec2.y), 2));
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

int	err_msg(char *msg, int return_val)
{
	printf("%s", msg);
	return (return_val);
}
