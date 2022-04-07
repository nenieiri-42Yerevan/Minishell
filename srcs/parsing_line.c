/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:06:22 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/07 11:39:24 by vismaily         ###   ########.fr       */
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

static void command_free(t_command **command)
{
	int	i;

	i = -1;
	if (command != 0)
	{
		while ((*command)->args[++i] != 0)
			free((*command)->args[i]);
		if ((*command)->args != 0)
			free((*command)->args);
		if ((*command)->oper != 0)
			free((*command)->oper);
		if ((*command)->oper_value != 0)
			free((*command)->oper_value);
		free(*command);
	}
}

int	parsing_line(char *line, t_token **tokens)
{
	int			count;
	char		metachars[7];
	t_command	*command;

	*tokens = 0;
	ft_strlcpy(metachars, "<>| \t\n", 7);
	count = tokens_count(line, metachars);
	if (count > 0)
	{
		tokens_array(line, metachars, tokens);
		command_init(&command);
		parsing_command(tokens, command);

		int	i = -1;
		while (command->args[++i] != 0)
			printf("%d - %s\n", i, command->args[i]);
		printf("oper - %s\n", command->oper);
		printf("oper_value - %s\n", command->oper_value);

		lst_clear_token(tokens, &free);
		command_free(&command);
	}
	return (1);
}
