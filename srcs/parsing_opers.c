/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_opers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:05:52 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/17 18:56:52 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_line(char *tmp, char *line)
{
	char	*res;

	if (tmp == 0)
	{
		tmp = ft_calloc(sizeof(char), 1);
		if (tmp == 0)
			return (0);
		res = ft_strjoin(tmp, line);
	}
	else
		res = strjoin_base(tmp, line, '\n');
	free(tmp);
	free(line);
	return (res);
}

static char	*heredoc(t_command *command)
{
	char	*line;
	char	*tmp;
	char	*res;

	tmp = 0;
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, command->oper_value, \
					ft_strlen(command->oper_value) + 1) == 0)
			break ;
		res = get_line(tmp, line);
		tmp = res;
	}
	if (line != 0)
		free(line);
	if (tmp != 0)
		free(tmp);
	return (res);
}

static int	parsing_ins(t_token **tokens, t_command *command)
{
	int	fd;

	(void)tokens;
	if (ft_strncmp(command->oper, "<", 2) == 0)
	{
		fd = open(command->oper_value, O_RDONLY);
		if (fd < 0)
			return (-1);
		if (command->std_in != 0)
			close(command->std_in);
		command->std_in = fd;
	}
	else if (ft_strncmp(command->oper, "<<", 3) == 0)
		command->heredoc = heredoc(command);
	return (0);
}

static int	parsing_redirs(t_token **tokens, t_command *command, t_token **tmp)
{
	int	fd;

	command->oper_value = ft_strdup((*tokens)->value);
	*tmp = *tokens;
	*tokens = (*tokens)->next;
	lst_delone_token(*tmp, &free);
	if (ft_strncmp(command->oper, ">", 2) == 0)
	{
		fd = open(command->oper_value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (command->std_out != 1)
			close(command->std_out);
		command->std_out = fd;
	}
	else if (ft_strncmp(command->oper, ">>", 3) == 0)
	{
		fd = open(command->oper_value, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (command->std_out != 1)
			close(command->std_out);
		command->std_out = fd;
	}
	else
		return (parsing_ins(tokens, command));
	return (0);
}

int	parsing_opers(t_token **tokens, t_command *command)
{
	t_token	*tmp;
	int		status;

	status = 0;
	while (*tokens != 0 && (*tokens)->type != 'c')
	{
		command->oper = ft_strdup((*tokens)->value);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		lst_delone_token(tmp, &free);
		if (*tokens != 0 && (*tokens)->type == 'v')
			status = parsing_redirs(tokens, command, &tmp);
		else
		{
			printf("Minishell$ Syntax error: Undefined value after operator\n");
			return (-1);
		}
	}
	return (status);
}
