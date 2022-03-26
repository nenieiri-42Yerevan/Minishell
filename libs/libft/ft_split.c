/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 21:29:50 by vismaily          #+#    #+#             */
/*   Updated: 2021/07/18 21:19:56 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	lenght(char const *s, char c)
{
	size_t	len;
	size_t	amount;

	amount = 0;
	while (*s)
	{
		len = 0;
		while (*s != c && *s)
		{
			++len;
			++s;
		}
		if (len != 0)
		{
			++amount;
			--s;
		}
		++s;
	}
	return (amount);
}

static void	ft_next_size(char const **s, size_t *next, char c)
{
	size_t	index;

	*s += *next;
	*next = 0;
	index = 0;
	while (**s && **s == c)
		++(*s);
	while ((*s)[index])
	{
		if ((*s)[index] == c)
			return ;
		++(*next);
		++index;
	}
}

static char	**ft_memory_error(char **s)
{
	size_t	index;

	index = 0;
	while (s[index])
	{
		free(s[index]);
		++index;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	len;
	size_t	sp_len;
	size_t	sp_index;

	if (!s)
		return (NULL);
	sp_len = lenght(s, c);
	res = (char **)malloc(sizeof(char *) * (sp_len + 1));
	if (!res)
		return (NULL);
	len = 0;
	sp_index = 0;
	while (sp_index < sp_len)
	{
		ft_next_size(&s, &len, c);
		res[sp_index] = malloc(sizeof(char) * (len + 1));
		if (!res[sp_index])
			return (ft_memory_error(res));
		ft_strlcpy(res[sp_index], s, len + 1);
		++sp_index;
	}
	res[sp_index] = NULL;
	return (res);
}
