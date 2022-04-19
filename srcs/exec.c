/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:18:39 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/19 18:15:54 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(char *path, t_command *command, char **envp)
{
	int		i;

	if (command->std_in != 0)
		dup2(command->std_in, 0);
	if (command->std_out != 1)
		dup2(command->std_out, 1);
	i = execve(path, command->args, envp);
	if (i == -1)
		printf("Minishell$ command not found: %s\n", command->args[0]);
}

void	exec(t_command *command, t_token **tokens, t_var **env_lst)
{
	char	**envp;
	char	*path;
	int		my_pid;
	int		exit_status;

	(void)tokens;
	path = find_command(command, *env_lst);
	envp = env_lst_to_arr(*env_lst);
	my_pid = fork();
	if (my_pid == 0)
		child(path, command, envp);
	else
	{
		wait(&exit_status);
		if (command->std_in != 0)
			close(command->std_in);
		if (command->std_out != 1)
			close(command->std_out);
		free(path);
		arr_free(envp);
	}
}
