/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_unquote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:11:34 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/09 23:50:17 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expansion(char *str, int *i, t_var *env_lst)
{
	char	*new_str;
	char	*ret_str;
	int		j;
	int		count;
	int		flag;

	count = *i;
	j = *i;
	flag = 0;
	while (str[j] != ' ' && str[j] != '\0' && str[j] != '\t' && str[j] != '\"')
		j++;
	new_str = ft_substr(str, *i + 1, j - count - 1);
	while (env_lst != 0)
	{
		if (ft_strncmp(env_lst->name, new_str, ft_strlen(new_str) + 1) == 0)
		{
			flag = 1;
			break ;
		}
		env_lst = env_lst->next;
	}
	if (flag == 1)
		ret_str = ft_strdup(env_lst->value);
	else
		ret_str = ft_strjoin("$", new_str);
	free(new_str);
	return (ret_str);
}

static void	double_quote(char *str, int *i, t_var *env_lst)
{
	char	*new_str;
	int		j;

	str[*i] = '\0';
	new_str = ft_strjoin(str, str + *i + 1);
	free(str);
	str = new_str;
	j = *i;
	while (str[j] != '\"')
	{
		if (str[j] == '$')
		{
			expansion(str, i, env_lst);
			printf("AAA %d\n", j);
		}
		j++;
	}
	str[j] = '\0';
	new_str = ft_strjoin(str, str + j + 1);
	free(str);
	str = new_str;
	*i = j - 1;
}

static void	single_quote(char *str, int *i)
{
	char	*new_str;
	int		j;

	str[*i] = '\0';
	new_str = ft_strjoin(str, str + *i + 1);
	free(str);
	str = new_str;
	j = *i;
	while (str[j] != '\'')
		j++;
	str[j] = '\0';
	new_str = ft_strjoin(str, str + j + 1);
	free(str);
	str = new_str;
	*i = j - 1;
}

static char	*str_unquote(char *str, t_var *env_lst)
{
	int		i;

	i = -1;
	while (str[++i] != 0)
	{
		if (str[i] == '\'')
			single_quote(str, &i);
		else if (str[i] == '\"')
			double_quote(str, &i, env_lst);
		else if (str[i] == '$')
			expansion(str, &i, env_lst);
	}
	return (str);
}

void	tokens_unquote(t_token *tokens, t_var *env_lst)
{
	char	*new_str;

	while (tokens != 0)
	{
		if (tokens->type == 'w')
		{
			new_str = str_unquote(tokens->value, env_lst);
			free(tokens->value);
			tokens->value = new_str;
		}
		tokens = tokens->next;
	}
}
