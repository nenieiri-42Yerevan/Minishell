/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:09:38 by vismaily          #+#    #+#             */
/*   Updated: 2021/07/18 21:09:10 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*new_dst;
	unsigned char	*new_src;

	new_dst = (unsigned char *)dst;
	new_src = (unsigned char *)src;
	while (n--)
	{
		*new_dst = *new_src;
		if (*new_src == (unsigned char)c)
			return ((void *)new_dst + 1);
		new_dst++;
		new_src++;
	}
	return (0);
}
