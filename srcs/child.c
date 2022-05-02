/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 14:46:45 by vismaily          #+#    #+#             */
/*   Updated: 2022/05/02 11:45:36 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*close_pipes(t_command **command, int id)
{
	t_command	*tmp;

	tmp = *command;
	while (tmp != 0)
	{
		if (tmp->id != id)
		{
			if (tmp->std_in != 0)
				close(tmp->std_in);
			if (tmp->std_out != 1)
				close(tmp->std_out);
			if (tmp->pipe_out != 0)
				close(tmp->pipe_out);
			if (tmp->pipe_in != 0)
				close(tmp->pipe_in);
		}
		tmp = tmp->next;
	}
	tmp = *command;
	while (tmp->id != id)
		tmp = tmp->next;
	dups(tmp);
	return (tmp);
}

void	child(t_command **command, t_var **env_lst, int id)
{
	int			i;
	char		**envp;
	t_command	*exec_com;

	exec_com = close_pipes(command, id);
	exec_com->path = find_command(exec_com, *env_lst);
	if (exec_com->path == 0)
	{
		if (exec_com->path_error == 0)
			exit(0);
		perror(exec_com->args[0]);
		exit(127);
	}
	if (exec_com->builtin != 1)
	{
		envp = env_lst_to_arr(*env_lst, 'e', 0);
		i = execve(exec_com->path, exec_com->args, envp);
		if (i == -1)
			printf("Minishell$ command not found: %s\n", exec_com->args[0]);
		exit (2);
	}
	else
		exec_builtin(exec_com, env_lst, 1);
}
