/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 17:35:07 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/23 17:44:02 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_status(t_var **env_lst, char *status)
{
	t_var	*tmp;

	tmp = *env_lst;
	while (tmp->meaning != '?')
		tmp = tmp->next;
	free(tmp->value);
	tmp->value = ft_strdup(status);
}
