/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_delone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:44:38 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/04 20:50:47 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_delone(t_var *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->name);
		del(lst->value);
		free (lst);
	}
}

void	lst_delone_token(t_token *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->value);
		free (lst);
	}
}
