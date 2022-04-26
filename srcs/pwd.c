/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:10:27 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/26 14:19:52 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_var **env_lst)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir == 0)
	{
		errno = 127;
		change_status(env_lst, 2);
		perror("pwd");
		return (2);
	}
	else
	{
		printf("%s\n", dir);
		free(dir);
		change_status(env_lst, 0);
		return (0);
	}
}
