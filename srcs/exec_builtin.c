/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:53:24 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/25 15:15:25 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_run(t_command *command, t_var **env_lst)
{
	if (ft_strncmp(command->path, "pwd", 4) == 0)
		pwd(env_lst);
	else if (ft_strncmp(command->path, "env", 4) == 0)
		env(env_lst);
	else if (ft_strncmp(command->path, "unset", 6) == 0)
		unset(command, env_lst);
	else if (ft_strncmp(command->path, "export", 7) == 0)
		export_env(command, env_lst);
	else if (ft_strncmp(command->path, "echo", 5) == 0)
		echo(command, env_lst);
	else if (ft_strncmp(command->path, "exit", 5) == 0)
		my_exit(command, env_lst);
}

void	exec_builtin(t_command *command, t_var **env_lst, int child_parent)
{
	if (child_parent == 0 && (command->oper == 0 || \
				ft_strncmp(command->oper, "|", ft_strlen(command->oper)) != 0))
		exec_run(command, env_lst);
	else if (child_parent == 1 && ft_strncmp(command->oper, "|", \
				ft_strlen(command->oper)) == 0)
	{
		exec_run(command, env_lst);
		exit (0);
	}
}
