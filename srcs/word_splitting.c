/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:07:23 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/11 21:11:43 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_ifs(t_token **tokens, t_token *tmp, char *ifs, int *i)
{
	char	*new_str;

	tmp->value[*i] = '\0';
	tmp->quote[*i] = '\0';
}

static void	search_ifs(t_token **tokens, char *ifs)
{
	t_token	*tmp;
	int		i;

	tmp = *tokens;
	while (tmp != 0)
	{
		i = -1;
		while (tmp->value[++i] != '\0')
		{
			if (tmp->value[i] == '\'' && tmp->quote[i] == '1')
				while (!(tmp->value[++i] == '\'' && tmp->quote[i] == '1'))
					;
			else if (tmp->value[i] == '\"' && tmp->quote[i] == '1')
				while (!(tmp->value[++i] == '\"' && tmp->quote[i] == '1'))
					;
			else if (ft_strchr(ifs, tmp->value[i]) != 0)
			{
				split_ifs(tokens, tmp, ifs, &i);
				break ;
			}
		}
		tmp = tmp->next;
	}
}

void	word_splitting(t_token **tokens, t_var *env_lst)
{

	while (env_lst != 0)
	{
		if (ft_strncmp(env_lst->name, "IFS", 4) == 0)
			break ;
		env_lst = env_lst->next;
	}
	if (env_lst != 0)
		search_ifs(tokens, env_lst->value);
}
