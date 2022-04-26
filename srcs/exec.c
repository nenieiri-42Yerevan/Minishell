/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:18:39 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/26 22:44:18 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (tmp->pipe_out != 0)
			close(tmp->pipe_out);
		if (tmp->pipe_in != 0)
			close(tmp->pipe_in);
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
}

static void	exec_in_proc(t_command **command, t_var **env_lst)
{
	int			my_pid;
	t_command	*tmp;
	t_command	*tmp2;

	tmp = *command;
	tmp2 = tmp;
	my_pid = 1;
	while (tmp != 0 && my_pid != 0)
	{
		if (tmp->id == 0 || tmp2->pipe == 1)
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

void	exec(t_command **command, t_var **env_lst)
{
	(*command)->path = find_command(*command, *env_lst);
	if ((*command)->builtin == 1 && (*command)->next == 0)
		exec_builtin(*command, env_lst, 0);
	else
		exec_in_proc(command, env_lst);
}
