/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:14:31 by vismaily          #+#    #+#             */
/*   Updated: 2022/03/28 10:29:30 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	t_env	**env_lst;

	if (argc > 1)
	{
		printf("The program no needs to arguments\n");
		return (0);
	}
	env_lst = env_to_list(envp);
	while (*env_lst)
	{
		printf("%s\n", (*env_lst)->name);
		(*env_lst)=(*env_lst)->next;
	}
	return (0);
}
