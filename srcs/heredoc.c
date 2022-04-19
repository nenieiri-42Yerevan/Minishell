/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 20:18:11 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/19 15:53:41 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_line(char *tmp, char *line)
{
	char	*res;

	if (tmp == 0)
	{
		tmp = ft_calloc(1, sizeof(char));
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

static char	*line_expansion(char *line, t_var *env_lst)
{
	t_token	*tmp;
	char	*str;

	tmp = (t_token *)malloc(sizeof(t_token));
	if (tmp == 0)
		return (0);
	tmp->value = line;
	tmp->type = 'w';
	tmp->quote = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (tmp->quote == 0)
		return (0);
	tmp->quote[ft_strlen(line)] = '\0';
	tmp->quote = (char *)ft_memset(tmp->quote, '0', ft_strlen(line));
	tmp->next = 0;
	p_expansion(tmp, env_lst);
	free(tmp->quote);
	str = tmp->value;
	free(tmp);
	return (str);
}

char	*heredoc(t_command *command, t_var *env_lst)
{
	char	*line;
	char	*tmp;
	char	*res;

	tmp = 0;
	res = 0;
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, command->oper_value, \
					ft_strlen(command->oper_value) + 1) == 0)
			break ;
		if (command->delimitor == 'h')
			line = line_expansion(line, env_lst);
		res = get_line(tmp, line);
		tmp = res;
	}
	if (line != 0)
		free(line);
	return (res);
}
