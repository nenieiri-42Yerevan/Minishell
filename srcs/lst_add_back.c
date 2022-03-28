/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:47:48 by vismaily          #+#    #+#             */
/*   Updated: 2022/03/28 11:10:11 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_add_back(t_env **lst, t_env *new_node)
{
	t_env	*tmp;

	if (lst)
	{
		if (*lst == 0)
			*lst = new_node;
		else
		{
			tmp = lst_last(*lst);
			tmp->next = new_node;
		}
	}
}
