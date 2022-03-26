/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:29:28 by vismaily          #+#    #+#             */
/*   Updated: 2021/02/01 01:17:08 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*new_dst;
	char	*new_src;

	if (!dst && !src)
		return (0);
	new_dst = (char *)dst;
	new_src = (char *)src;
	i = 0;
	if (new_dst > new_src)
		while (++i <= len)
			new_dst[len - i] = new_src[len - i];
	else
		while (len--)
			*new_dst++ = *new_src++;
	return (dst);
}
