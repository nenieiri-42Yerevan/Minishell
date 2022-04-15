/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:18:39 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/15 20:47:10 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(t_var *env_lst, char *command)
{
	char	**path;
	char	*value;
	int		i;

	i = -1;
	path = 0;
	while (env_lst != 0)
	{
		if (ft_strncmp(env_lst->name, "PATH", 5) == 0)
		{
			path = ft_split(env_lst->value, ':');
			break ;
		}
		env_lst = env_lst->next;
	}
	while (path != 0 && path[++i] != 0)
	{
		value = strjoin_base(path[i], command, '/');
		if (access(value, F_OK | X_OK) == 0)
		{
			arr_free(path);
			return (value);
		}
		free(value);
	}
	arr_free(path);
	return (0);
}

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
	envp = env_lst_to_arr(*env_lst);
	if (ft_strchr(command->args[0], '/') != 0)
		path = ft_strdup(command->args[0]);
	else
	{
		path = find_path(*env_lst, command->args[0]);
		if (path != 0)
			command->args[0] = ft_strdup(path);
	}
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
