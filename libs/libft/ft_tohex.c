/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 21:42:19 by vismaily          #+#    #+#             */
/*   Updated: 2021/11/27 21:44:06 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tohex(int n)
{
	char	*hex;
	int		temp;
	int		i;

	i = 0;
	hex = ft_calloc(sizeof(char), 100);
	while (n != 0)
	{
		temp = n % 16;
		if (temp < 10)
			temp += 48;
		else
			temp += 55;
		hex[i++] = temp;
		n /= 16;
	}
	hex[i] = '\0';
	return (hex);
}
