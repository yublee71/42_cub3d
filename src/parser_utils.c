/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:26:50 by mayeung           #+#    #+#             */
/*   Updated: 2025/05/06 17:51:13 by mayeung          ###   ########.fr       */
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
		return (ft_putstr_fd("Null argument\n", STDERR_FILENO), ERR);
	if (!path || ft_strlen(path) < ft_strlen(".cub"))
		return (ft_putstr_fd("File name too short\n", STDERR_FILENO), ERR);
	if (!ft_strrchr(path, '.')
		|| ft_strncmp(ft_strrchr(path, '.'), ".cub", ft_strlen(".cub") + 1))
		return (ft_putstr_fd("File name not end with .cub\n", STDERR_FILENO),
			ERR);
	return (OK);
}
