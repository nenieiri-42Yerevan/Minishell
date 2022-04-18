/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:30:05 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/18 16:04:29 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parsing_final(t_token **tokens, t_var *env_lst)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != 0 && tmp->type != 'c')
	{
		quote_counting(tmp);
		p_expansion(tmp, env_lst);
		tmp = tmp->next;
	}
	word_splitting(tokens, env_lst);
	tmp = *tokens;
	while (tmp != 0 && tmp->type != 'c')
	{
		if (tmp->type != 'r')
			quote_removal(tmp);
		tmp = tmp->next;
	}
}

int	parsing_command(t_token **tokens, t_command *command, t_var **env_lst)
{
	parsing_final(tokens, *env_lst);
	arg_count(tokens, command);
	if (parsing_opers(tokens, command) == -1)
		return (-1);
	return (0);
}
