/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:22:35 by vismaily          #+#    #+#             */
/*   Updated: 2022/03/27 21:01:19 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*lst_last(t_env *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (0);
}

static void	lst_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (lst)
	{
		if (*lst == 0)
			*lst = new;
		else
		{
			tmp = lst_last(*lst);
			tmp->next = new;
		}
	}
}

static t_env	*lst_new_elem(char *name, char *value)
{
	t_env	*new_elem;

	new_elem = (t_env *)malloc(sizeof(t_env));
	if (!new_elem)
		return (0);
	new_elem->name = name;
	new_elem->value = value;
	new_elem->next = 0;
	return (new_elem);
}

t_env	**env_to_list(char **envp)
{
	int		i;
	char	*eq;
	t_env	**env_lst;
	t_env	*node;

	i = 0;
	while (envp[i] != 0)
		i++;
	env_lst = (t_env **)ft_calloc(sizeof(t_env *), i + 1);
	i = 0;
	while (envp[i] != 0)
	{
		eq = ft_strchr(envp[i], '=');
		*eq = '\0';
		node = lst_new_elem(envp[i], eq + 1);
		lst_add_back(env_lst, node);
		i++;
	}
	return (env_lst);
}
