/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:26:41 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/20 13:40:32 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != 0)
		printf("%s\n", envp[i]);
	if (envp[i] == 0)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
