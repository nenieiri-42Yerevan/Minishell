/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 22:27:29 by vismaily          #+#    #+#             */
/*   Updated: 2021/07/18 21:15:14 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*newelem;

	if (!lst || !f)
		return (0);
	newlist = 0;
	while (lst)
	{
		newelem = ft_lstnew(f(lst->content));
		if (!newelem)
		{
			ft_lstclear(&newlist, del);
			return (0);
		}
		ft_lstadd_back(&newlist, newelem);
		lst = lst->next;
	}
	return (newlist);
}
