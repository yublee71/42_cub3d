/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:32:00 by yublee            #+#    #+#             */
/*   Updated: 2023/11/20 14:36:20 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Iterates the list ’lst’ and applies the function
 * ’f’ on the content of each node. Creates a new
 * list resulting of the successive applications of
 * the function ’f’. The ’del’ function is used to
 * delete the content of a node if needed.
 */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*result;

	if (!lst || !f || !del)
		return (NULL);
	result = ft_lstnew(f(lst->content));
	if (!result)
		return (NULL);
	temp = result;
	lst = lst->next;
	while (lst)
	{
		temp->next = ft_lstnew(f(lst->content));
		if (!temp->next)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		temp = temp->next;
		lst = lst->next;
	}
	return (result);
}
