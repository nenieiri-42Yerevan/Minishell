/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:23:05 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/02 20:44:50 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}			t_var;

t_var		**env_to_list(char **envp);
t_var		*lst_last(t_var *lst);
void		lst_add_back(t_var **lst, t_var *new_node);
t_var		*lst_new_elem(char *name, char *value);
int			parsing_line(char *line);
int			tokens_count(char *line, char *metachars);
void		tokens_array(char *line, char **tokens, char *metachars);

#endif
