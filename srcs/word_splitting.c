/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:07:23 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/11 20:22:21 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	word_splitting(t_token **tokens)
{
	t_token	*tmp;
	int		i;

	tmp = *tokens;
	while (tmp != 0)
	{
		i = -1;
		tmp = tmp->next;
	}
}
