/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:06:22 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/09 23:53:12 by vismaily         ###   ########.fr       */
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
		free(*command);
	}
}

int	parsing_line(char *line, t_token **tokens, t_var **env_lst)
{
	int			count;
	char		metachars[11];
//	t_command	*command;

	*tokens = 0;
	ft_strlcpy(metachars, "<>|&;() \t\n", 11);
	count = tokens_count(line, metachars);
	if (count > 0)
	{
		tokens_array(line, metachars, tokens, *env_lst);
	//	parsing_command(tokens, &command);
		//exec(command, tokens, env_lst);
		lst_clear_token(tokens, &free);
		(void)command_free;
	//	command_free(&command);
	}
	return (1);
}
