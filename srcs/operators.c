/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:02:02 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/17 17:43:15 by vismaily         ###   ########.fr       */
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
				printf("Miniahell$ Syntax error: unexpected token '%s'\n", \
						tokens->value);
				return (-1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}
