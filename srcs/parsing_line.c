/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:06:22 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/14 16:50:15 by vismaily         ###   ########.fr       */
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
	(*command)->next = 0;
}

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
		command_init(&command);
		parsing_command(tokens, &command, env_lst);
//		exec(command, tokens, env_lst);
//		lst_clear_token(tokens, &free);
		(void)command_free;
	//	command_free(&command);
	//	tokens_unquote(**tokens, env_lst);
	//	tokens_trim(tokens);
		int j = -1;
		while (command->args[++j] != 0)
			printf("%s\n", command->args[j]);
		printf("________________\n");
		while (*tokens != 0)
		{
			printf("%c %s\n", (*tokens)->type, (*tokens)->value);
			*tokens = (*tokens)->next;
		}
	}
	return (1);
}
