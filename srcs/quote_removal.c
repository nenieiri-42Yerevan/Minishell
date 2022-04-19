/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:21:33 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/18 21:21:08 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_removal(t_token *tokens)
{
	int		i;
	char	*new_value;
	char	*new_quote;

	i = -1;
	while (tokens->value[++i] != '\0')
	{
		if ((tokens->value[i] == '\'' || tokens->value[i] == '\"') && \
				tokens->quote[i] == '1')
		{
			tokens->value[i] = '\0';
			new_value = ft_strjoin(tokens->value, tokens->value + i + 1);
			free(tokens->value);
			tokens->value = new_value;
			tokens->quote[i] = '\0';
			new_quote = ft_strjoin(tokens->quote, tokens->quote + i + 1);
			free(tokens->quote);
			tokens->quote = new_quote;
			--i;
			if (tokens->type == 'h')
				tokens->type = 'H';
		}
	}
}
