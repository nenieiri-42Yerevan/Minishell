/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 20:10:46 by vismaily          #+#    #+#             */
/*   Updated: 2021/09/03 20:21:26 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char			*new_s1;
	unsigned int	i;

	i = -1;
	new_s1 = (char *)malloc(sizeof(char) * (n + 1));
	if (new_s1 == NULL)
		return (NULL);
	while (++i < n && s1[i] != '\0')
		new_s1[i] = s1[i];
	new_s1[i] = '\0';
	return (new_s1);
}
