/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:10:27 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/20 14:54:35 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir == 0)
	{
		printf("pwd not found\n");
		return (EXIT_FAILURE);
	}
	else
	{
		printf("%s\n", dir);
		return (EXIT_SUCCESS);
	}
}
