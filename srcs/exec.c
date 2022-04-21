/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:18:39 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/21 16:26:36 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin(char *path, t_command *command, t_var **env_lst)
{
	int	status;

	status = 0;
	if (ft_strncmp(path, "pwd", 4) == 0)
		status = pwd();
	else if (ft_strncmp(path, "env", 4) == 0)
		status = env(env_lst);
	else if (ft_strncmp(path, "unset", 6) == 0)
		status = unset(command, env_lst);
	else if (ft_strncmp(path, "export", 7) == 0)
		status = export_env(command, env_lst);
	return (status);
}

static void	child(char *path, t_command *command, t_var **env_lst)
{
	int		i;
	int		heredoc[2];
	char	**envp;

	if (command->std_in != 0)
		dup2(command->std_in, 0);
	if (command->std_out != 1)
		dup2(command->std_out, 1);
	if (command->oper != 0 && \
			ft_strncmp(command->oper, "<<", 3) == 0 && command->heredoc != 0)
	{
		i = pipe(heredoc);
		if (i == -1)
			exit(1);
		ft_putstr_fd(command->heredoc, heredoc[1]);
		ft_putstr_fd("\n", heredoc[1]);
		dup2(heredoc[0], 0);
		close(heredoc[0]);
		close(heredoc[1]);
	}
	if (command->builtin != 1)
	{
		envp = env_lst_to_arr(*env_lst, 'e', 0);
		i = execve(path, command->args, envp);
		if (i == -1)
			printf("Minishell$ command not found: %s\n", command->args[0]);
	}
	else
		exec_builtin(path, command, env_lst);
}

void	exec(t_command **command, t_token **tokens, t_var **env_lst)
{
	char	*path;
	int		my_pid;
	int		exit_status;

	(void)tokens;
	path = find_command(*command, *env_lst);
	my_pid = fork();
	if (my_pid == 0)
		child(path, *command, env_lst);
	else
	{
		wait(&exit_status);
		if ((*command)->std_in != 0)
			close((*command)->std_in);
		if ((*command)->std_out != 1)
			close((*command)->std_out);
		free(path);
	}
}
