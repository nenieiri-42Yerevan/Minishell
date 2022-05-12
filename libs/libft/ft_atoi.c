/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:12:50 by vismaily          #+#    #+#             */
/*   Updated: 2022/05/12 16:33:41 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_and_return(const char *str, int *k)
{
	char	*new_str;

	new_str = (char *)str;
	*k = 1;
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("Minishell: exit: ", 2);
	ft_putstr_fd(new_str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (255);
}

static int	check_max_long_int(const char *str, int i, int *k)
{
	int		sign;
	char	max_long[20];

	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (ft_strlen(&(str[i])) > 19)
		return (print_and_return(str, k));
	else if (ft_strlen(&str[i]) == 19)
	{
		if (sign == 1)
			ft_strlcpy(max_long, "9223372036854775807", 20);
		else
			ft_strlcpy(max_long, "9223372036854775808", 20);
		if (ft_strncmp(&(str[i]), max_long, 20) > 0)
			return (print_and_return(str, k));
	}
	return (0);
}

long	ft_atoi(const char *str, int *k)
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
	if (check_max_long_int(str, i, k) == 255)
		return (255);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}
