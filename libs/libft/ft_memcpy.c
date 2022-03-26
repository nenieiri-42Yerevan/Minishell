/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 00:35:49 by vismaily          #+#    #+#             */
/*   Updated: 2021/07/18 21:08:56 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*new_dst;
	char	*new_src;

	if (!dst && !src)
		return (0);
	new_dst = (char *)dst;
	new_src = (char *)src;
	while (n--)
		*new_dst++ = *new_src++;
	return (dst);
}
