/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:23:59 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/03 15:58:48 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	quotes(char *line, int *i, char c)
{
	size_t	len;

	len = 0;
	if (line[*i] == c)
	{
		len = *i;
		(*i)++;
		while (line[*i] != c)
			(*i)++;
		(*i)++;
		len = *i - len;
	}
	return (len);
}

static size_t	words_and_ops(char *line, char *metachars, int *i)
{
	size_t	len;

	len = 0;
	if (ft_strchr(metachars, line[*i]) != 0)
	{	
		len = *i;
		while (ft_strchr(metachars, line[*i]) != 0 && line[*i] != '\0')
			(*i)++;
		len = *i - len;
	}
	else if (line[*i] != ' ' && line[*i] != '\'' && line[*i] != '\"')
	{
		len = *i;
		while (ft_strchr(metachars, line[*i]) == 0 && \
				line[*i] != '\0' && line[*i] != ' ' && line[*i] != '\'' && \
				line[*i] != '\"')
			(*i)++;
		len = *i - len;
	}
	return (len);
}

static size_t	spaces(char *line, int *i)
{
	int	word_len;

	word_len = 0;
	while (line[*i] == ' ')
	{
		word_len = 1;
		(*i)++;
	}
	return (word_len);
}

static void	word_malloc(t_token **tokens, int *j, size_t word_len, char *line)
{
	if (word_len != 0)
	{
		tokens[*j] = malloc(sizeof(t_token));
		tokens[*j]->value = malloc(sizeof(char) * (word_len + 1));
		ft_strlcpy(tokens[*j]->value, line, word_len + 1);
		if (tokens[*j]->value[0] == '\'')
			tokens[*j]->type = 's';
		else if (tokens[*j]->value[0] == '\"')
			tokens[*j]->type = 'd';
		else if (ft_strchr("<>|", tokens[*j]->value[0]) != 0)
			tokens[*j]->type = 'o';
		else
			tokens[*j]->type = 'w';
		(*j)++;
	}
}

void	tokens_array(char *line, t_token **tokens, char *metachars)
{
	int		i;
	int		j;
	size_t	word_len;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		word_len = spaces(line, &i);
		word_len = quotes(line, &i, '\'');
		word_malloc(tokens, &j, word_len, line + i - word_len);
		word_len = quotes(line, &i, '\"');
		word_malloc(tokens, &j, word_len, line + i - word_len);
		if (line[i] == '\0')
			break ;
		word_len = words_and_ops(line, metachars, &i);
		word_malloc(tokens, &j, word_len, line + i - word_len);
	}
}
