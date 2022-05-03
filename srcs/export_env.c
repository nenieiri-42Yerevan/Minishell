/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:06:34 by vismaily          #+#    #+#             */
/*   Updated: 2022/05/03 12:46:47 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_env(t_var **env_lst)
{
	int		i;
	char	**envp;

	i = -1;
	envp = env_lst_to_arr(*env_lst, 'x', 1);
	while (envp[++i] != 0)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
	}
	if (envp[i] == 0)
	{	
		arr_free(envp);
		change_status(env_lst, 0);
		return (0);
	}
	else
	{
		arr_free(envp);
		change_status(env_lst, 1);
		return (2);
	}
}

static t_var	*env_var_update(t_var **env_lst, char *before_eq, \
		char *after_eq, char meaning)
{
	t_var	*tmp;

	tmp = *env_lst;
	while (tmp != 0)
	{
		if (ft_strncmp(tmp->name, before_eq, ft_strlen(tmp->name) + 1) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(after_eq);
			tmp->meaning = meaning;
			break ;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

static void	export_new(t_var **env_lst, char *before_eq, \
		char *after_eq, char meaning)
{
	char	*name;
	char	*value;
	t_var	*node;
	t_var	*tmp;

	tmp = env_var_update(env_lst, before_eq, after_eq, meaning);
	if (tmp == 0)
	{
		name = ft_strdup(before_eq);
		value = ft_strdup(after_eq);
		node = lst_new_elem(name, value);
		node->meaning = meaning;
		node->next = 0;
		lst_add_back(env_lst, node);
	}
}

static int	export_arg(t_command *command, int i, int *res, t_var **env_lst)
{
	char	*eq;

	if (command->args[i][0] != '=' && ft_strchr(command->args[i], '=') != 0)
	{
		eq = ft_strchr(command->args[i], '=');
		*eq = '\0';
		if (check_var_name(command->args[i], res, env_lst) == 1)
			return (1);
		export_new(env_lst, command->args[i], eq + 1, 'e');
	}
	else
	{
		if (check_var_name(command->args[i], res, env_lst) == 1)
			return (1);
		export_new(env_lst, command->args[i], "", 'x');
	}
	return (0);
}

int	export_env(t_command *command, t_var **env_lst)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	if (command->args[1] == 0)
		return (print_env(env_lst));
	else
	{
		while (command->args[++i] != 0)
			export_arg(command, i, &res, env_lst);
		if (res == 0)
			change_status(env_lst, 0);
		else
			change_status(env_lst, 1);
		return (0);
	}
}
