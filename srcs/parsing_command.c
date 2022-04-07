/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:30:05 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/07 11:39:06 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	arg_to_array(t_token **tokens, t_command *command, char c, int i)
{
	int		count;
	t_token	*tmp;

	count = 0;
	if (c == 'n')
	{
		tmp = *tokens;
		while (tmp != 0 && tmp->type != 'o')
		{
			count++;
			tmp = tmp->next;
		}
		command->args = (char **)malloc(sizeof(char *) * (count + 1));
		command->args[count] = 0;
	}
	command->args[i] = ft_strdup((*tokens)->value);
	tmp = *tokens;
	*tokens = (*tokens)->next;
	lst_delone_token(tmp, &free);
}

void	parsing_command(t_token **tokens, t_command *command)
{
	int		i;
	t_token	*tmp;

	i = -1;
	while (*tokens != 0 && (*tokens)->type != 'o')
	{
		if (i++ == -1 && (*tokens)->type == 'w')
			arg_to_array(tokens, command, 'n', i);
		else
			arg_to_array(tokens, command, 'o', i);
	}
	if (*tokens != 0)
	{
		command->oper = ft_strdup((*tokens)->value);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		lst_delone_token(tmp, &free);
	}
	if (*tokens != 0)
	{
		command->oper_value = ft_strdup((*tokens)->value);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		lst_delone_token(tmp, &free);
		command->balance = *tokens;
	}
}
