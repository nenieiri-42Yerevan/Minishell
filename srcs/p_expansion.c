/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:00:36 by vismaily          #+#    #+#             */
/*   Updated: 2022/06/04 12:57:29 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	my_replace(t_token *tokens, int i, int j, t_var *env_lst)
{
	char	*new_value;
	char	*new_blank;
	char	*new_str;

	new_value = ft_strdup(env_lst->value);
	tokens->value[i] = '\0';
	new_str = ft_strjoin(tokens->value, new_value);
	free(new_value);
	new_value = ft_strjoin(new_str, tokens->value + j);
	free(new_str);
	free(tokens->value);
	tokens->value = new_value;
	new_blank = (char *)malloc(sizeof(char) * (ft_strlen(env_lst->value) + 1));
	if (new_blank == 0)
		return (-1);
	new_blank[ft_strlen(env_lst->value)] = '\0';
	ft_memset(new_blank, '2', ft_strlen(env_lst->value));
	tokens->quote[i] = '\0';
	new_str = ft_strjoin(tokens->quote, new_blank);
	free(new_blank);
	new_blank = ft_strjoin(new_str, tokens->quote + j);
	free(new_str);
	free(tokens->quote);
	tokens->quote = new_blank;
	return (0);
}

static int	not_found_2(t_token *tokens, int *i, int j, t_var *tmp)
{
	if ((j - *i) == 1 && (tmp->name[0] == '1' || \
			(tokens->value[j] != '\"' && tokens->value[j] != '\'')))
		tmp->value = (char *)malloc(sizeof(char) * 2);
	else
		tmp->value = (char *)malloc(sizeof(char) * 1);
	if (tmp->value == 0)
		return (-1);
	if ((j - *i) == 1 && (tmp->name[0] == '1' || \
			(tokens->value[j] != '\"' && tokens->value[j] != '\'')))
	{
		tmp->value[0] = '$';
		tmp->value[1] = '\0';
	}
	else
		tmp->value[0] = '\0';
	tmp->next = 0;
	return (1);
}

static int	not_found(t_token *tokens, int *i, int j, int quote)
{
	t_var	*tmp;
	int		res;

	tmp = (t_var *)malloc(sizeof(t_var) * 1);
	if (tmp == 0)
		return (-1);
	tmp->name = (char *)malloc(sizeof(char) * 2);
	if (tmp->name == 0)
		return (-1);
	if (quote == 1)
		tmp->name[0] = '1';
	else
		tmp->name[0] = '0';
	tmp->name[1] = '\0';
	not_found_2(tokens, i, j, tmp);
	res = my_replace(tokens, *i, j, tmp);
	if (!((j - *i) == 1 && (tmp->name[0] == '1' || \
			(tokens->value[j] == '\"' || tokens->value[j] == '\''))))
		*i = *i - 1;
	lst_delone(tmp, &free);
	return (res);
}

static int	search_and_replace(t_token *t, int *i, t_var *env_lst, int q)
{
	char	*new_str;
	int		j;

	j = *i + 1;
	while (t->value[j] != ' ' && t->value[j] != '\0' && t->value[j] != '\t' && \
			t->value[j] != '\"' && t->value[j] != '\'' && t->value[j] != '/' \
			&& t->value[j] != '$' && t->value[j] != '=')
		j++;
	new_str = ft_substr(t->value, *i + 1, j - *i - 1);
	while (env_lst != 0)
	{
		if (ft_strncmp(env_lst->name, new_str, ft_strlen(new_str) + 1) == 0)
			break ;
		env_lst = env_lst->next;
	}
	if (new_str[0] == '\0')
	{
		free(new_str);
		return (0);
	}
	free(new_str);
	if (env_lst != 0)
		return (my_replace(t, *i, j, env_lst));
	else
		return (not_found(t, i, j, q));
}

void	p_expansion(t_token *tokens, t_var *env_lst)
{
	int		i;

	i = -1;
	while (tokens->value[++i] != '\0')
	{
		if (tokens->value[i] == '\'')
		{
			i++;
			while (tokens->value[i] != '\'' && tokens->value[i] != '\0')
				i++;
		}
		else if (tokens->value[i] == '\"')
		{
			while (tokens->value[++i] != '\"')
				if (tokens->value[i] == '$')
					search_and_replace(tokens, &i, env_lst, 1);
		}
		else if (tokens->value[i] == '$')
			search_and_replace(tokens, &i, env_lst, 0);
	}
}
