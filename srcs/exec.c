/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:18:39 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/09 16:30:19 by vismaily         ###   ########.fr       */
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
	if (path != 0)
	{
		while (path[++i] != 0)
		{
			value = ft_strjoin(path[i], command);
			if (access(value, F_OK | X_OK) == 0)
			{
				//arr_free(path);
				return (value);
			}
			//free(value);
		}
	}
	//arr_free(path);
	return (0);
}

void	exec(t_command *command, t_token **tokens, t_var **env_lst)
{
	char	**envp;
	char	*path;
	int		i;

	(void)tokens;
	envp = env_lst_to_arr(*env_lst);
	path = find_path(*env_lst, command->args[0]);
	i = execve(command->args[0], command->args, envp);
	//arr_free(envp);
}
