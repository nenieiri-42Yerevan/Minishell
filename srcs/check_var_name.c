/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:45:12 by vismaily          #+#    #+#             */
/*   Updated: 2022/05/03 10:56:20 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *str)
{
	char	*tmp;
	char	*err;

	tmp = ft_strjoin(str, "': not a valid identifier\n");
	err = ft_strjoin("Minishell: '", tmp);
	free(tmp);
	ft_putstr_fd(err, 2);
	free(err);
}

int	check_var_name(char *str, int *res, t_var **env_lst)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (i == 0 && ((str[0] == '_') || (str[0] >= 'a' && str[0] <= 'z') || \
				(str[0] >= 'A' && str[0] <= 'Z')))
			continue ;
		else if (i != 0 &&  ((str[i] >= 48 && str[i] <= 57) || \
				(str[i] >= 'a' && str[i] <= 'z') || \
				(str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_')))
			continue ;
		else
		{
			print_error(str);
			change_status(env_lst, 1);
			*res = 1;
			return (1);
		}
	}
	return (0);
}
