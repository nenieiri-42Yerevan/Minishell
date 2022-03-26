/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:28:08 by vismaily          #+#    #+#             */
/*   Updated: 2021/07/18 21:04:48 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	abs_value(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	get_len(int n)
{
	int		len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;

	len = get_len(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	result[len] = '\0';
	if (n < 0)
		result[0] = '-';
	else if (n == 0)
		result[0] = '0';
	while (n != 0)
	{
		len--;
		result[len] = abs_value(n % 10) + '0';
		n /= 10;
	}
	return (result);
}
