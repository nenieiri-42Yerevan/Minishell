/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:26:41 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/20 20:57:05 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_var **env_lst)
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
		return (EXIT_SUCCESS);
	}
	else
	{
		arr_free(envp);
		return (EXIT_FAILURE);
	}
}
