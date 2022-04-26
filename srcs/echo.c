/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:25:03 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/26 14:15:21 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char *str, int *n)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (i == 0 && str[i] == '-')
			continue ;
		else if (i != 0 && str[i] == 'n')
			continue ;
		else
			break ;
	}
	if (i != 0 && str[i] == '\0')
	{
		*n = 1;
		return (1);
	}
	return (0);
}

static int	echo_print(t_command *command, int *i)
{
	int	flag;
	int	status;

	flag = 0;
	status = 0;
	while (command->args[*i] != 0)
	{
		if (flag == 1)
			status = printf(" ");
		if (status < 0)
			return (status);
		status = printf("%s", command->args[*i]);
		if (status < 0)
			return (status);
		flag = 1;
		++(*i);
	}
	return (0);
}

int	echo(t_command *command, t_var **env_lst)
{
	int	n;
	int	i;
	int	status;

	n = 0;
	status = 0;
	if (command->args[1] == 0)
		printf("\n");
	else
	{
		i = 0;
		while (command->args[++i] != 0 && check_flag(command->args[i], &n) == 1)
			;
		status = echo_print(command, &i);
		if (n == 0 && status >= 0)
			status = printf("\n");
	}
	if (status < 0)
	{
		errno = 127;
		change_status(env_lst, 127);
		return (2);
	}
	change_status(env_lst, 0);
	return (0);
}
