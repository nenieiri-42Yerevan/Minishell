/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:30:05 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/07 15:41:05 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	command_init(t_command **command)
{
	(*command) = (t_command *)malloc(sizeof(t_command));
	(*command)->args = 0;
	(*command)->oper = 0;
	(*command)->oper_value = 0;
	(*command)->std_in = 0;
	(*command)->std_out = 1;
	(*command)->std_err = 2;
	(*command)->balance = 0;
}

static void	arg_to_array(t_token **tokens, t_command *command, int i)
{
	int		count;
	t_token	*tmp;

	count = 0;
	if (i == 0)
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

void	parsing_command(t_token **tokens, t_command **command)
{
	int		i;
	t_token	*tmp;

	i = -1;
	command_init(command);
	while (*tokens != 0 && (*tokens)->type != 'o')
		arg_to_array(tokens, *command, ++i);
	if (*tokens != 0)
	{
		(*command)->oper = ft_strdup((*tokens)->value);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		lst_delone_token(tmp, &free);
	}
	if (*tokens != 0)
	{
		(*command)->oper_value = ft_strdup((*tokens)->value);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		lst_delone_token(tmp, &free);
		(*command)->balance = *tokens;
	}
}
