/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_to_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:18:41 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/24 16:08:21 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	my_size(t_var *lst, char meaning)
{
	int	count;

	count = 0;
	while (lst != 0)
	{
		if ((meaning == 'x' && (lst->meaning == 'e' || lst->meaning == 'x')) \
				|| (meaning == 'e' && lst->meaning == 'e'))
			count++;
		lst = lst->next;
	}
	return (count);
}

static void	find_and_join(t_var *env_lst, int quote, char **arr, int *i)
{
	char	*tmp;

	if (quote == 1)
	{
		if (ft_strncmp(env_lst->value, "", ft_strlen(env_lst->value)) != 0)
		{
			tmp = ft_strjoin(env_lst->name, "=\"");
			arr[*i] = ft_strjoin(tmp, env_lst->value);
			free(tmp);
			tmp = arr[*i];
			arr[*i] = ft_strjoin(tmp, "\"");
			free(tmp);
		}
		else
			arr[*i] = ft_strdup(env_lst->name);
		*i = *i + 1;
	}
	else
	{
		arr[*i] = strjoin_base(env_lst->name, env_lst->value, '=');
		*i = *i + 1;
	}
}

char	**env_lst_to_arr(t_var *env_lst, char meaning, int quote)
{
	int		size;
	int		i;
	char	**arr;

	i = 0;
	size = my_size(env_lst, meaning);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (arr == 0)
		return (0);
	arr[size] = 0;
	while (env_lst != 0)
	{
		if ((meaning == 'x' && (env_lst->meaning == 'e' || \
						env_lst->meaning == 'x')) || (meaning == 'e' && \
						env_lst->meaning == 'e'))
			find_and_join(env_lst, quote, arr, &i);
		env_lst = env_lst->next;
	}
	return (arr);
}
