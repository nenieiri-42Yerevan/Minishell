/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:18:39 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/24 18:11:05 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	builtin_runs(t_command **command, t_var **env_lst)
{
	t_command	*exec_com;

	exec_com = *command;
	while (exec_com != 0 && exec_com->path == 0)
	{
		exec_com->path = find_command(exec_com, *env_lst);
		exec_com = exec_com->next;
	}
	if ((*command)->builtin == 1)
		exec_builtin(*command, env_lst, 0);
}

static void	parent(t_command **command, t_var **env_lst)
{
	int			exit_status;
	int			status_code;
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
	while (wait(&exit_status) != -1 || errno != ECHILD)
	{
		if (WIFEXITED(exit_status))
		{
			status_code = WEXITSTATUS(exit_status);
			change_status(env_lst, status_code);
		}
	}
	builtin_runs(command, env_lst);
}

void	exec(t_command **command, t_var **env_lst)
{
	int			my_pid;
	t_command	*tmp;
	t_command	*tmp2;

	tmp = *command;
	tmp2 = tmp;
	my_pid = 1;
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
		parent(command, env_lst);
}
