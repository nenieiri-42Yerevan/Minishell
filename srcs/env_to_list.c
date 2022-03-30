/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:22:35 by vismaily          #+#    #+#             */
/*   Updated: 2022/03/29 19:02:02 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_var	*env_content(char *before_eq, char *after_eq)
{
	char	*name;
	char	*value;
	t_var	*node;

	name = ft_strdup(before_eq);
	value = ft_strdup(after_eq);
	node = lst_new_elem(name, value);
	return (node);
}

t_var	**env_to_list(char **envp)
{
	int		i;
	char	*eq;
	t_var	**env_lst;
	t_var	*node;

	i = 0;
	while (envp[i] != 0)
		i++;
	env_lst = (t_var **)ft_calloc(sizeof(t_var *), i + 1);
	i = 0;
	while (envp[i] != 0)
	{
		eq = ft_strchr(envp[i], '=');
		*eq = '\0';
		node = env_content(envp[i], eq + 1);
		lst_add_back(env_lst, node);
		i++;
	}
	return (env_lst);
}
