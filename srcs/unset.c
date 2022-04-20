/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:46:44 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/20 14:54:58 by vismaily         ###   ########.fr       */
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

static void	unset_vars(t_command *command, t_var **env_lst)
{
	t_var	*tmp;
	int		i;

	i = 0;
	while (command->args[++i] != 0)
	{
		if (ft_strncmp(command->args[i], (*env_lst)->name, \
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

int	unset(t_command *command, t_var **env_lst, char **envp)
{
	if (env_lst != 0 && command != 0)
	{
		if (command->args[1] == 0)
		{
			printf("unset: not enough arguments\n");
			return (EXIT_FAILURE);
		}
		else
			unset_vars(command, env_lst);
	}
	arr_free(envp);
	envp = env_lst_to_arr(*env_lst);
	return (EXIT_SUCCESS);
}
