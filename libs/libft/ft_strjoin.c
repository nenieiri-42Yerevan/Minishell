/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:31:04 by vismaily          #+#    #+#             */
/*   Updated: 2021/01/25 22:10:54 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*newstr;
	size_t			i;
	size_t			j;

	newstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!newstr)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}
