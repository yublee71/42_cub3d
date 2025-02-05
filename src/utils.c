/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:52:21 by yublee            #+#    #+#             */
/*   Updated: 2025/02/05 19:58:06 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	get_vector_length(t_vec raydir)
{
	double	length;
	
	length = sqrt(pow(raydir.x, 2) + pow(raydir.y, 2));
	return (length);
}

t_vec	rotate_vector(t_vec	vec, int degree)
{
	t_vec	rotated_vec;
	double	radian;
	
	radian = M_PI / 180 * degree;
	rotated_vec.x = vec.x * cos(radian) - vec.y * sin(radian);
	rotated_vec.y = vec.x * sin(radian) + vec.y * cos(radian);
	return (rotated_vec);
}

int	err_msg(char *msg, int return_val)
{
	printf("%s", msg);
	return (return_val);
}
