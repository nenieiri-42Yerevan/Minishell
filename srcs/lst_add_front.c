/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 17:39:55 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/23 17:44:49 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_add_front(t_var **lst, t_var *new_elem)
{
	if (lst && new_elem)
	{
		new_elem->next = *lst;
		*lst = new_elem;
	}
}
