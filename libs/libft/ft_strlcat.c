/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 13:08:22 by vismaily          #+#    #+#             */
/*   Updated: 2021/07/18 20:58:14 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	while (src[k] != '\0')
		k++;
	if (dstsize <= i)
		return (dstsize + k);
	if (dstsize > i)
	{
		while (j < dstsize - i - 1 && src[j] != '\0')
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
	}
	return (i + k);
}
