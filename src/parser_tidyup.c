/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tidyup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:26:50 by mayeung           #+#    #+#             */
/*   Updated: 2025/04/22 16:32:41 by mayeung          ###   ########.fr       */
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
