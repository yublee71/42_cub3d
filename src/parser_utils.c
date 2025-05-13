/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:26:50 by mayeung           #+#    #+#             */
/*   Updated: 2025/05/13 20:56:13 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	copy_to_map(t_parse *parse)
{
	size_t	i;
	t_list	*node;

	if (!parse)
		return (ERR);
	parse->vars->map = ft_calloc((ft_lstsize(parse->map) + 1), sizeof(char *));
	if (!parse->vars->map)
		return (ERR);
	i = 0;
	node = parse->map;
	while (node)
	{
		parse->vars->map[i++] = node->content;
		node = node->next;
	}
	return (OK);
}

void	empty_function(void *arg)
{
	(void)arg;
}

void	free_content(void *arg)
{
	free(arg);
}

int	check_map_name(char *path)
{
	if (!path)
		return (err_msg("Error\nNull argument\n", ERR));
	if (!path || ft_strlen(path) < ft_strlen(".cub"))
		return (err_msg("Error\nFile name too short\n", ERR));
	if (!ft_strrchr(path, '.')
		|| ft_strncmp(ft_strrchr(path, '.'), ".cub", ft_strlen(".cub") + 1))
		return (err_msg("Error\nFile name not end with .cub\n",
				ERR));
	return (OK);
}
