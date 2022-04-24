/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:26:41 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/24 17:12:09 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_var **env_lst)
{
	int		i;
	char	**envp;

	i = -1;
	envp = env_lst_to_arr(*env_lst, 'e', 0);
	while (envp[++i] != 0)
		printf("%s\n", envp[i]);
	if (envp[i] == 0)
	{
		arr_free(envp);
		change_status(env_lst, 0);
	}
	else
	{
		arr_free(envp);
		change_status(env_lst, 127);
		exit(2);
	}
}
