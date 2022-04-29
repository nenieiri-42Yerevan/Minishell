/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:06:22 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/29 11:48:39 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_all(t_command **command, t_token **tokens)
{
	lst_clear_token(tokens, &free);
	while (*command != 0)
	{
		command_free(*command);
		*command = (*command)->next;
	}
}

static int	command_bld(t_token **tokens, t_var **env_lst, t_command **command)
{
	if (tokens_to_struct(tokens, command, env_lst) == -1)
	{
		change_status(env_lst, 1);
		perror(NULL);
		return (-1);
	}
	return (0);
}

int	parsing_line(char *line, t_token **tokens, t_var **env_lst,\
	   	struct s_signal *signals)
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
		if (command_bld(tokens, env_lst, &command) == 0)
			exec(&command, env_lst, signals);
		clear_all(&command, tokens);
	}
	return (1);
}
