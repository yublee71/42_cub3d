/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:31:52 by yublee            #+#    #+#             */
/*   Updated: 2023/11/20 14:32:59 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
lst: The address of a pointer to a node.
f: The address of the function used to iterate on
the list.
*/

/**
 * lst: The address of a pointer to a node.
 * f: The address of the function used to iterate on
 * the list.
 * Iterates the list ’lst’ and applies the function
 * ’f’ on the content of each node.
 */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	if (!lst || !f)
		return ;
	temp = lst;
	while (temp->next)
	{
		f(temp->content);
		temp = temp->next;
	}
	f(temp->content);
}
