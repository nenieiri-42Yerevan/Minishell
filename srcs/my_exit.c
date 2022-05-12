/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:15:41 by vismaily          #+#    #+#             */
/*   Updated: 2022/05/12 15:46:48 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_status_correct(long res)
{
	double	num;
	long	int_part;

	if (res >= 0 && res <= 255)
		return (res);
	num = (double)res / 256;
	printf("%f \n", num);
	int_part = (long)num;
	num = (num - int_part) * 256;
	if (num >= ((long)num + 0.5))
		res = (long)num + 1;
	else
		res = (long)num;
	if (res < 0)
		return (256 + res);
	else
		return (res);
}

static int	parsing_code(t_command *command, int *k)
{
	long	res;
	int		i;

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
		*k = 1;
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("Minishell:: exit: ", 2);
		ft_putstr_fd(command->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		res = 255;
	}
	return (res);
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
	int	res;
	int	k;

	k = 0;
	if (command->args[1] != 0)
	{
		res = parsing_code(command, &k);
		if (command->args[2] == 0 && k == 0)
			ft_putstr_fd("exit\n", 1);
		if (command->args[2] != 0 && k == 0)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
			change_status(env_lst, 1);
			return (2);
		}
		change_status(env_lst, res);
		run_exit(*env_lst);
	}
	else
		run_exit(*env_lst);
	return (0);
}
