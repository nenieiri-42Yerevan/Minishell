/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 20:18:11 by vismaily          #+#    #+#             */
/*   Updated: 2022/05/03 12:22:15 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	go_heredoc(t_command *command, t_var *env_lst, int fd_doc)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, command->oper_value, \
					ft_strlen(command->oper_value) + 1) == 0)
			break ;
		if (command->delimitor == 'h')
			line = line_expansion(line, env_lst);
		ft_putstr_fd(line, fd_doc);
		ft_putstr_fd("\n", fd_doc);
		free(line);
	}
	if (line != 0)
		free(line);
}

static void	child_heredoc(t_command *command, t_var **env_lst, int *heredoc)
{
	signal(SIGINT, handle_sigint_heredoc);
	close(heredoc[0]);
	go_heredoc(command, *env_lst, heredoc[1]);
	close(heredoc[1]);
	exit(0);
}

static int parent_heredoc(t_command *command, int *heredoc)
{
	int	exit_status;

	signal(SIGINT, SIG_IGN);
	wait(&exit_status);
	close(heredoc[1]);
	if (WIFEXITED(exit_status))
	{
		exit_status = WEXITSTATUS(exit_status);
		if (exit_status == 1)
			return (-3);
		else
			command->std_in = dup(heredoc[0]);
		close(heredoc[0]);
	}
	signals_init();
	return (0);
}

int	heredoc(t_command *command, t_var **env_lst)
{
	int	pid;
	int	heredoc[2];
	int	i;
	
	i = pipe(heredoc);
	if (i == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
		child_heredoc(command, env_lst, heredoc);
	else
		return (parent_heredoc(command, heredoc));
	return (0);
}
