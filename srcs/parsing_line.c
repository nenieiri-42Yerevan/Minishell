/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:06:22 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/05 18:23:49 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_line(char *line)
{
	int		count;
	char	metachars[7];
	t_token	*tokens;

	tokens = 0;
	ft_strlcpy(metachars, "<>| \t\n", 7);
	count = tokens_count(line, metachars);
	if (count > 0)
	{
		tokens_array(line, metachars, &tokens);
	
	/*	while (tokens != 0)
		{
			printf("%c %s\n", tokens->type, tokens->value);
			tokens=tokens->next;
		}
*/
		lst_clear_token(&tokens, &free);
	}
	return (1);
}
