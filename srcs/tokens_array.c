/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:23:59 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/10 17:09:57 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	word_malloc(t_token **tokens, int *j, size_t *word_len, char *line)
{
	t_token	*token_elem;
	char	*str;

	if (line != 0 && *word_len != 0)
	{
		str = (char *)malloc(sizeof(char) * (*word_len + 1));
		ft_strlcpy(str, line, *word_len + 1);
		if (ft_strchr("<>|&;() \t\n", str[0]) != 0)
			token_elem = lst_new_elem_token('o', str);
		else
			token_elem = lst_new_elem_token('w', str);
		lst_add_back_token(tokens, token_elem);
		(*j)++;
		line = 0;
		*word_len = 0;
	}
}

static char	*single_quotes(char *line, int *i, size_t *word, char *metachars)
{
	if (line[*i] == '\'')
	{
		(*word)++;
		(*i)++;
		while (line[*i] != '\'' && line[*i] != '\0')
		{
			(*word)++;
			(*i)++;
		}
		(*word)++;
		(*i)++;
		if (line[*i] == '\0' || ft_strchr(metachars, line[*i]) != 0)
			return (line + *i - *word);
	}
	return (0);
}

static char	*double_quotes(char *line, int *i, size_t *word, char *metachars)
{
	if (line[*i] == '\"')
	{
		(*word)++;
		(*i)++;
		while (line[*i] != '\"' && line[*i] != '\0')
		{
			(*word)++;
			(*i)++;
		}
		(*word)++;
		(*i)++;
		if (line[*i] == '\0' || ft_strchr(metachars, line[*i]) != 0)
			return (line + *i - *word);
	}
	return (0);
}

static char	*words_and_ops(char	*line, int *i, size_t *word, char *metachars)
{
	if (ft_strchr(metachars, line[*i]) != 0 && line[*i] != '\0')
	{
		while (ft_strchr(metachars, line[*i]) != 0 && line[*i] != '\0')
		{
			(*word)++;
			(*i)++;
		}
		return (line + *i - *word);
	}
	else if (line[*i] != '\'' && line[*i] != '\"' && line[*i] != '\0')
	{
		while (ft_strchr(metachars, line[*i]) == 0 && \
				line[*i] != '\0' && line[*i] != '\'' && line[*i] != '\"')
		{
			(*word)++;
			(*i)++;
		}
		if ((line[*i] != '\'' && line[*i] != '\"') || line[*i] == '\0')
			return (line + *i - *word);
	}
	return (0);
}

void	tokens_array(char *line, char *metachars, t_token **tokens)
{
	int		i;
	int		j;
	size_t	word_len;
	char	*start;

	i = 0;
	j = 0;
	word_len = 0;
	while (line[i] != '\0')
	{
		start = single_quotes(line, &i, &word_len, metachars);
		word_malloc(tokens, &j, &word_len, start);
		start = double_quotes(line, &i, &word_len, metachars);
		word_malloc(tokens, &j, &word_len, start);
		start = words_and_ops(line, &i, &word_len, metachars);
		word_malloc(tokens, &j, &word_len, start);
	}
	tokens_trim(tokens);
}
