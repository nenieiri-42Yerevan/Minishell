/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:46:44 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/30 18:43:52 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_and_del(t_command *command, t_var **env_lst, int i)
{
	t_var	*tmp;
	t_var	*tmp2;

	tmp = *env_lst;
	while (tmp != 0)
	{
		if (tmp->next != 0 && ft_strncmp(command->args[i], tmp->next->name, \
					ft_strlen(command->args[i]) + 1) == 0)
		{
			tmp2 = tmp->next;
			if (tmp->next->next != 0)
				tmp->next = tmp->next->next;
			else
				tmp->next = 0;
			lst_delone(tmp2, &free);
		}
		else
			tmp = tmp->next;
	}
}

static int	checked(char *str, int *res, t_var **env_lst)
{
	if ((str[0] == '_') || (str[0] >= 'a' && str[0] <= 'z') || \
			(str[0] >= 'A' && str[0] <= 'Z'))
		return (0);
	else
	{
		perror(str);
		change_status(env_lst, 1);
		*res = 1;
		return (1);
	}
}

static void	pwd_imitation(t_var *env_lst)
{
	while (env_lst != 0)
	{
		if (ft_strncmp(env_lst->name, "PWD", 4) == 0)
		{
			env_lst->meaning = 'p';
			break ;
		}
		env_lst = env_lst->next;
	}
}

static void	unset_vars(t_command *command, t_var **env_lst, int *res)
{
	t_var	*tmp;
	int		i;

	i = 0;
	while (command->args[++i] != 0)
	{
		if (checked(command->args[i], res, env_lst) == 0)
		{
			if (ft_strncmp(command->args[i], "PWD", 4) == 0)
				pwd_imitation(*env_lst);
			else if (ft_strncmp(command->args[i], (*env_lst)->name, \
						ft_strlen(command->args[i]) + 1) == 0)
			{
				tmp = *env_lst;
				*env_lst = (*env_lst)->next;
				lst_delone(tmp, &free);
				continue ;
			}
			else
				find_and_del(command, env_lst, i);
		}
	}
}

int	unset(t_command *command, t_var **env_lst)
{
	int	res;

	res = 0;
	if (env_lst != 0 && command != 0)
	{
		if (command->args[1] == 0)
			change_status(env_lst, 0);
		else
			unset_vars(command, env_lst, &res);
	}
	if (res == 0)
		change_status(env_lst, 0);
	else
		change_status(env_lst, 1);
	return (0);
}
