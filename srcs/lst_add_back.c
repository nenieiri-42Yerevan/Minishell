/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:47:48 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/04 17:45:57 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_add_back(t_var **lst, t_var *new_node)
{
	t_var	*tmp;

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

void	lst_add_back_token(t_token **lst, t_token *new_node)
{
	t_token	*tmp;

	if (lst)
	{
		if (*lst == 0)
			*lst = new_node;
		else
		{
			tmp = lst_last_token(*lst);
			tmp->next = new_node;
		}
	}
}
