/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:15:41 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/26 14:17:09 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_status_correct(int res)
{
	float	num;
	int		int_part;

	if (res >= 0 && res <= 255)
		return (res);
	num = (float)res / 256;
	int_part = (int)num;
	num =  (num - int_part) * 256;
	if (num >= ((int)num + 0.5))
		res = (int)num + 1;
	else
		res = (int)num;
	if (res < 0)
		return (256 + res);
	else
		return (res);
}

static void	parsing_code(t_command *command, t_var **env_lst)
{
	int	res;
	int	i;

	i = -1;
	while (command->args[1][++i] != '\0') 
		if (!(ft_isdigit(command->args[1][i]) == 1 || \
				(i == 0 && command->args[1][i] == '-')))
			break ;
	if (command->args[1][i] == '\0')
	{
		res = ft_atoi(command->args[1]);
		res = exit_status_correct(res);
	}
	else
	{
		errno = 255;
		perror(command->args[1]);
		res = 255;
	}
	change_status(env_lst, res);
}

static void	run_exit(t_var *env_lst)
{
	while (env_lst->meaning != '?')
		env_lst = env_lst->next;
	if (env_lst->value != 0)
		free(env_lst->value);
	env_lst->value = ft_strdup("exit");
}

int	my_exit(t_command *command, t_var **env_lst)
{
	if (command->args[1] != 0)
	{
		parsing_code(command, env_lst);
		run_exit(*env_lst);
	}
	else
		run_exit(*env_lst);
	if (command->args[1] != 0 && command->args[2] != 0)
	{
		errno = 1;
		perror("exit");
	}
	return (0);
}
