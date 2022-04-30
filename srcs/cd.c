/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:33:42 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/30 15:22:30 by vismaily         ###   ########.fr       */
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
	int	j;

	j = 0;
	while (env_lst != 0)
	{
		if (ft_strncmp(env_lst->name, "PWD", 4) == 0)
		{
			free(env_lst->value);
			env_lst->value = getcwd(NULL, 0);
		}
		else if (ft_strncmp(env_lst->name, "OLDPWD", 7) == 0 && oldpwd != 0)
		{
			free(env_lst->value);
			env_lst->value = oldpwd;
			j++;
		}
		env_lst = env_lst->next;
	}
	if (j == 0)
		free(oldpwd);
}

static int	change(char *path, t_var **env_lst)
{
	char	*oldpwd;

	oldpwd = getold(env_lst);
	if (chdir(path) == -1)
	{
		perror(path);
		free(path);
		if (oldpwd != 0)
			free(oldpwd);
		change_status(env_lst, 1);
		return (2);
	}
	else
	{
		change_env(oldpwd, *env_lst);
		free(path);
		change_status(env_lst, 0);
		return (0);
	}
}

static int	find_home(t_var **env_lst, char **path)
{
	t_var	*tmp;

	tmp = *env_lst;
	while (tmp != 0)
	{
		if (ft_strncmp(tmp->name, "HOME", 5) == 0)
		{
			*path = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp == 0)
	{
		perror("Minishell: cd: HOME not set");
		change_status(env_lst, 1);
		return (-1);
	}
	return (0);
}

int	cd(t_command *command, t_var **env_lst)
{
	char	*path;
	int		res;

	res = 0;
	if (command->args[1] == 0)
		res = find_home(env_lst, &path);
	else
		path = ft_strdup(command->args[1]);
	if (res == 0)
		res = change(path, env_lst);
	return (res);
}
