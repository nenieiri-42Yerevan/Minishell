/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:06:22 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/18 17:00:45 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	command_free(t_command **command)
{
	int	i;

	i = -1;
	if (command != 0)
	{
		if ((*command)->args != 0)
		{
			while ((*command)->args[++i] != 0)
				free((*command)->args[i]);
			free((*command)->args);
		}
		if ((*command)->oper != 0)
			free((*command)->oper);
		if ((*command)->oper_value != 0)
			free((*command)->oper_value);
		if ((*command)->heredoc != 0)
			free((*command)->heredoc);
		free(*command);
	}
}

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
		//exec(command, tokens, env_lst);
		lst_clear_token(tokens, &free);
		t_command *tmp = command;
		while (tmp != 0)
		{
			int j = -1;
			while (tmp->args[++j] != 0)
				printf("%s\n", tmp->args[j]);
			if (tmp->heredoc != 0)
				printf("%s\n", tmp->heredoc);
			printf("________________\n");
			tmp = tmp->next;
		}
		(void)command_free;
		//command_free(&command);
	}
	return (1);
}
