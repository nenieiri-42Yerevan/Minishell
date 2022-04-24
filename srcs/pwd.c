/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:10:27 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/24 20:17:19 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_var **env_lst)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir == 0)
	{
		errno = 127;
		change_status(env_lst, 2);
		perror("pwd");
		exit(2);
	}
	else
	{
		printf("%s\n", dir);
		free(dir);
		change_status(env_lst, 0);
	}
}
