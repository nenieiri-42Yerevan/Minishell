/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:48:39 by vismaily          #+#    #+#             */
/*   Updated: 2022/03/28 11:11:14 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*lst_new_elem(char *name, char *value)
{
	t_env	*new_elem;

	new_elem = (t_env *)malloc(sizeof(t_env));
	if (!new_elem)
		return (0);
	new_elem->name = name;
	new_elem->value = value;
	new_elem->next = 0;
	return (new_elem);
}
