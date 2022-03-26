/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 13:52:45 by vismaily          #+#    #+#             */
/*   Updated: 2021/01/24 14:30:24 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		len;

	len = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)s + len);
	while (len--)
	{
		if (*(s + len) == c)
			return ((char *)(s + len));
	}
	return (0);
}
