/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:30:05 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/14 18:55:27 by vismaily         ###   ########.fr       */
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

/*void	parsing_opers(t_token **tokens, t_command **command)
{
	t_token	*tmp;

	if ((ft_strncmp((*tokens)->value, ">>", 3) == 0) || \
			(ft_strncmp((*tokens)->value, ">", 2) == 0))
	{
		(*command)->oper = ft_strdup((*tokens)->value);
		if (ft_strncmp((*tokens)->value, ">", 2) == 0)
		{
		//	open();
		}
		tmp = *tokens;
		*tokens = (*tokens)->next->next;
		lst_delone_token(tmp->next, &free);
		lst_delone_token(tmp, &free);
	}
}*/

void	parsing_command(t_token **tokens, t_command **command, t_var **env_lst)
{
	parsing_final(tokens, *env_lst);
	arg_count(tokens, *command);
//	if (*tokens != 0 && (*tokens)->type == 'o')
//		parsing_opers(tokens, command);
}
