/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:30:05 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/12 17:11:33 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parsing_final(t_token **tokens, t_var *env_lst)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != 0 && tmp->type != 'o')
	{
		quote_counting(tmp);
		p_expansion(tmp, env_lst);
		tmp = tmp->next;
	}
	word_splitting(tokens, env_lst);
	tmp = *tokens;
	while (tmp != 0 && tmp->type != 'o')
	{
		quote_removal(tmp);
		tmp = tmp->next;
	}
}

static int	arg_to_array(t_token **tokens, t_command *command, int i)
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
		if (command->args == 0)
			return (-1);
		command->args[count] = 0;
	}
	command->args[i] = ft_strdup((*tokens)->value);
	tmp = *tokens;
	*tokens = (*tokens)->next;
	lst_delone_token(tmp, &free);
	return (0);
}

void	parsing_opers(t_token **tokens, t_command **command)
{
	t_token	*tmp;

	if ((ft_strncmp((*tokens)->value, ">>" 3) == 0) || \
			(ft_strncmp((*tokens)->value, ">" 2) == 0))
	{
		(*command)->oper = ft_strdup((*tokens)->value);
		if (ft_strncmp((*tokens)->value, ">" 2) == 0)
		{
			open();
		}
		tmp = *tokens;
		*tokens = (*tokens)->next->next;
		lst_delone_token(tmp->next, &free);
		lst_delone_token(tmp, &free);
	}
}

void	parsing_command(t_token **tokens, t_command **command, t_var **env_lst)
{
	int			i;

	i = -1;
	parsing_final(tokens, *env_lst);
	while (*tokens != 0 && (*tokens)->type != 'o')
		arg_to_array(tokens, *command, ++i);
	if (*tokens != 0 && (*tokens)->type == 'o')
		parsing_opers(tokens, *command);
}
