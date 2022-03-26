/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 11:04:19 by vismaily          #+#    #+#             */
/*   Updated: 2021/07/18 21:14:51 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*new_s1;
	unsigned char	*new_s2;

	new_s1 = (unsigned char *)s1;
	new_s2 = (unsigned char *)s2;
	while (n--)
	{
		if (*new_s1 != *new_s2)
			return (*new_s1 - *new_s2);
		else
		{
			new_s1++;
			new_s2++;
		}
	}
	return (0);
}
