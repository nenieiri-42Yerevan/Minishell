/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:47:38 by vismaily          #+#    #+#             */
/*   Updated: 2022/05/02 20:17:43 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getold(t_var **env_lst)
{
	t_var	*tmp;

	tmp = *env_lst;
	while (tmp != 0)
	{
		if (ft_strncmp(tmp->name, "PWD", 4) == 0 && tmp->meaning != 'p')
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (0);
}

static void	change_env(char *oldpwd, t_var *env_lst)
{
	while (env_lst != 0)
	{
		if (ft_strncmp(env_lst->name, "PWD", 4) == 0)
		{
			free(env_lst->value);
			env_lst->value = getcwd(NULL, 0);
		}
		else if (ft_strncmp(env_lst->name, "OLDPWD", 7) == 0)
		{
			if (env_lst->value != 0)
				free(env_lst->value);
			if (oldpwd == 0)
			{
				env_lst->value = ft_strdup("");
				env_lst->meaning = 'q';
			}
			else
				env_lst->value = ft_strdup(oldpwd);
		}
		env_lst = env_lst->next;
	}
}

static int	cd_parent(char *path, t_var **env_lst, char *oldpwd)
{
	int		exit_status;

	wait(&exit_status);
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	if (exit_status == 0 && chdir(path) == 0)
	{
		change_env(oldpwd, *env_lst);
		free(path);
		change_status(env_lst, 0);
		return (0);
	}
	if (exit_status != 0)
		ft_putstr_fd("cd: error retrieving current directory: getcwd: " \
				"cannot access parent directories: No such file or " \
				"directory\n", 2);
	else
		perror(path);
	free(path);
	if (oldpwd != 0)
		free(oldpwd);
	change_status(env_lst, 1);
	return (2);
}

int	change_dir(char *path, t_var **env_lst)
{
	char	*oldpwd;
	int		pid;

	oldpwd = getold(env_lst);
	pid = fork();
	if (pid == 0)
	{
		if (chdir(path) == 0 && getcwd(NULL, 0) == NULL)
			exit(1);
		exit(0);
	}
	else
		return (cd_parent(path, env_lst, oldpwd));
}
