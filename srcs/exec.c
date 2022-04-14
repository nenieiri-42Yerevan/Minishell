/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:18:39 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/14 16:34:14 by vismaily         ###   ########.fr       */
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

void	exec(t_command *command, t_token **tokens, t_var **env_lst)
{
	char	**envp;
	char	*path;
	int		i;
	int		my_pid;
	int		exit_status;
	int		fd;

	(void)tokens;
	envp = env_lst_to_arr(*env_lst);
	if (ft_strchr(command->args[0], '/') != 0)
		path = ft_strdup(command->args[0]);
	else
	{
		path = find_path(*env_lst, command->args[0]);
		command->args[0] = ft_strdup(path);
	}
	my_pid = fork();
	if (my_pid == 0)
	{
		if (ft_strncmp(command->oper, ">", 1) == 0)
		{
			printf("%s\n", command->oper_value);
			fd = open(command->oper_value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			printf("%d\n", fd);
			if (fd != -1)
			{
				dup2(fd, 1);
				close(fd);
			}
		}
		i = execve(path, command->args, envp);
	}
	else
	{
		wait(&exit_status);
		free(path);
		arr_free(envp);
	}
}
