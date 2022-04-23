/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:18:39 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/23 16:22:50 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent(t_command **command, int *exit_status)
{
	t_command	*tmp;

	tmp = *command;
	while (tmp != 0)
	{
		if (tmp->std_in != 0)
			close(tmp->std_in);
		if (tmp->std_out != 1)
			close(tmp->std_out);
		tmp = tmp->next;
	}
	while (wait(exit_status) != -1 || errno != ECHILD)
		;
}

void	exec(t_command **command, t_var **env_lst)
{
	int			my_pid;
	int			*exit_status;
	t_command	*tmp;
	t_command	*tmp2;

	tmp = *command;
	tmp2 = tmp;
	my_pid = 1;
	exit_status = 0;
	while (tmp != 0 && my_pid != 0)
	{
		if (tmp->id == 0 || ft_strncmp(tmp2->oper, "|", 2) == 0)
			my_pid = fork();
		if (my_pid == 0)
			child(command, env_lst, tmp->id);
		else if (tmp != 0)
		{
			tmp2 = tmp;
			tmp = tmp->next;
		}
	}
	if (my_pid != 0)
		parent(command, exit_status);
}
