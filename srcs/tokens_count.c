/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:06:03 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/03 15:02:12 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quotes(char *line, int *i, int *count, char c)
{
	if (line[*i] == c)
	{
		(*i)++;
		while (line[*i] != c && line[*i] != '\0')
			(*i)++;
		if (line[*i] == '\0')
		{
			printf("Error: found not closed quote\n");
			(*count) = -300;
		}
		(*count)++;
		(*i)++;
	}
}

static void	words_and_ops(char *line, char *metachars, int *i, int *count)
{
	if (ft_strchr(metachars, line[*i]) != 0)
	{	
		while (ft_strchr(metachars, line[*i]) != 0 && line[*i] != '\0')
			(*i)++;
		(*count)++;
	}
	else if (line[*i] != ' ' && line[*i] != '\'' && line[*i] != '\"')
	{
		while (ft_strchr(metachars, line[*i]) == 0 && \
				line[*i] != '\0' && line[*i] != ' ' && line[*i] != '\'' && \
				line[*i] != '\"')
			(*i)++;
		(*count)++;
	}
}

int	tokens_count(char *line, char *metachars)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		while (line[i] == ' ')
			i++;
		quotes(line, &i, &count, '\'');
		quotes(line, &i, &count, '\"');
		if (line[i] == '\0')
			break ;
		words_and_ops(line, metachars, &i, &count);
	}
	return (count);
}
