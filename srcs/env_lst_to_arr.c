/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_to_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:18:41 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/08 19:45:13 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strjoin_eq(char const *s1, char const *s2)
{
	char			*newstr;
	size_t			i;
	size_t			j;

	newstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (!newstr)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	newstr[i] = '=';
	j = 0;
	while (s2[j] != '\0')
	{
		newstr[i + 1 + j] = s2[j];
		j++;
	}
	newstr[i + j + 1] = '\0';
	return (newstr);
}
char	**env_lst_to_arr(t_var *env_lst)
{
	int		size;
	int		i;
	char	**arr;

	i = 0;
	size = lst_size(env_lst);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (arr == 0)
		return (0);
	arr[size] = 0;
	while (env_lst != 0)
	{
		arr[i++] = strjoin_eq(env_lst->name, env_lst->value);
		env_lst = env_lst->next;
	}
	return (arr);
}
