/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:06:22 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/03 15:43:04 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tokens_free(t_token **tokens)
{
	size_t	index;

	index = 0;
	while (tokens[index])
	{
		free(tokens[index]->value);
		free(tokens[index]);
		index++;
	}
	free(tokens);
}

int	parsing_line(char *line)
{
	int		count;
	t_token	**tokens;
	char	metachars[4];

	ft_strlcpy(metachars, "<>|", 4);
	count = tokens_count(line, metachars);
	if (count > 0)
	{
		tokens = malloc(sizeof(t_token) * (count + 1));
		if (tokens == 0)
			return (0);
		tokens[count] = 0;
		tokens_array(line, tokens, metachars);
	
		int	i = 0;
		while(tokens[i] != 0)
		{
			printf("%c %s\n", tokens[i]->type, tokens[i]->value);
			i++;
		}

		if (tokens != NULL)
			tokens_free(tokens);
	}
	return (1);
}
