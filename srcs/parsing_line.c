/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:06:22 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/19 17:33:40 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_line(char *line, t_token **tokens, t_var **env_lst)
{
	int			count;
	char		metachars[11];
	t_command	*command;

	*tokens = 0;
	command = 0;
	ft_strlcpy(metachars, "<>|&;() \t\n", 11);
	count = tokens_count(line, metachars);
	if (count > 0)
	{
		tokens_array(line, metachars, tokens);
		if (operators(*tokens) == -1)
		{
			lst_clear_token(tokens, &free);
			return (-1);
		}
		tokens_to_struct(tokens, &command, env_lst);
		exec(command, tokens, env_lst);
		lst_clear_token(tokens, &free);
	}
	return (1);
}
