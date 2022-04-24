/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 18:22:18 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/24 19:23:14 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	new_atoi(const char *str, int *lvl)
{
	long			res;
	int				sign;
	unsigned int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || \
str[i] == '\n' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	*lvl = res * sign;
	if (str[i] != '\0')
		return (0);
	else
		return (1);
}

static void	lvl_up(int lvl, t_var *tmp)
{
	if (lvl < 0)
		lvl = 0;
	else if (lvl >= 0 && lvl <= 999)
		lvl++;
	else
	{
		printf("Minishell: warning: shell level (%d) too high, "
			"resetting to 1\n", lvl + 1);
		lvl = 1;
	}
	if (lvl == 1000)
	{
		free(tmp->value);
		tmp->value = ft_strdup("");
	}
	else
	{
		free(tmp->value);
		tmp->value = ft_itoa(lvl);
	}
}

void	shlvl(t_var **env_lst)
{
	t_var	*new_elem;
	t_var	*tmp;
	int		lvl;

	tmp = *env_lst;
	while (tmp != 0)
	{
		if (ft_strncmp(tmp->name, "SHLVL", ft_strlen(tmp->name)) == 0)
		{
			if (new_atoi(tmp->value, &lvl) == 0)
				lvl = 1;
			lvl_up(lvl, tmp);
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp == 0)
	{
		new_elem = lst_new_elem(ft_strdup("SHLVL"), ft_strdup("1"));
		lst_add_back(env_lst, new_elem);
	}
}
