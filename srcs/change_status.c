/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 17:35:07 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/23 19:26:59 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_status(t_var **env_lst, int status)
{
	t_var	*tmp;

	tmp = *env_lst;
	while (tmp->meaning != '?')
		tmp = tmp->next;
	tmp->status = status;
	if (tmp->value != 0)
		free(tmp->value);
	tmp->value = ft_itoa(tmp->status);
}
