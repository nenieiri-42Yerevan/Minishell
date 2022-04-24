/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:22:35 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/24 19:19:21 by vismaily         ###   ########.fr       */
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
	node->next = 0;
	return (node);
}

static int	for_exit_status(t_var *node, t_var **env_lst)
{
	char	*blank;

	blank = malloc(sizeof(char) * 2);
	if (blank == 0)
		return (0);
	blank[0] = '0';
	blank[1] = '\0';
	node = lst_new_elem("?", blank);
	node->meaning = '?';
	node->status = 0;
	lst_add_front(env_lst, node);
	return (1);
}

int	env_to_list(char **envp, t_var **env_lst)
{
	int		i;
	char	*eq;
	t_var	*node;

	i = 0;
	*env_lst = 0;
	while (envp[i] != 0)
		i++;
	i = 0;
	while (envp[i] != 0)
	{
		eq = ft_strchr(envp[i], '=');
		*eq = '\0';
		node = env_content(envp[i], eq + 1);
		lst_add_back(env_lst, node);
		i++;
	}
	return (for_exit_status(node, env_lst));
}
