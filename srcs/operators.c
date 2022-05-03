/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:02:02 by vismaily          #+#    #+#             */
/*   Updated: 2022/05/03 11:42:52 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	operators(t_token *tokens)
{
	while (tokens != 0)
	{
		if (tokens->type == 'o')
		{
			if (ft_strncmp(tokens->value, ">", 2) == 0 || \
					ft_strncmp(tokens->value, ">>", 3) == 0 || \
					ft_strncmp(tokens->value, "<", 2) == 0 || \
					ft_strncmp(tokens->value, "<<", 3) == 0)
				tokens->type = 'r';
			else if (ft_strncmp(tokens->value, "|", 2) == 0)
				tokens->type = 'c';
			else
			{
				ft_putstr_fd("Minishell: Syntax error: unexpected token '", 2);
				ft_putstr_fd(tokens->value, 2);
				ft_putstr_fd("'\n", 2);
				return (-1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}
