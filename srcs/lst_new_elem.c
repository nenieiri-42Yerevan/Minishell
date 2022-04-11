/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:48:39 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/10 19:32:43 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*lst_new_elem(char *name, char *value)
{
	t_var	*new_elem;

	new_elem = (t_var *)malloc(sizeof(t_var));
	if (!new_elem)
		return (0);
	new_elem->name = name;
	new_elem->value = value;
	new_elem->next = 0;
	return (new_elem);
}

t_token	*lst_new_elem_token(char type, char *value)
{
	t_token	*new_elem;

	new_elem = (t_token *)malloc(sizeof(t_token));
	if (!new_elem)
		return (0);
	new_elem->type = type;
	new_elem->value = value;
	new_elem->quote = (char *)ft_calloc(sizeof(char), (ft_strlen(value) + 1));
	new_elem->quote[sizeof(char) * ft_strlen(value)] = '\0';
	new_elem->next = 0;
	return (new_elem);
}
