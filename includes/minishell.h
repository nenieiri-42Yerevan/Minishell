/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:23:05 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/06 15:08:03 by vismaily         ###   ########.fr       */
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
}					t_var;

typedef struct s_token
{
	char			type;
	char			*value;
	struct s_token	*next;
}					t_token;

t_var		*lst_new_elem(char *name, char *value);
t_var		*lst_last(t_var *lst);
void		lst_add_back(t_var **lst, t_var *new_node);
void		lst_delone(t_var *lst, void (*del)(void *));
void		lst_clear(t_var **lst, void (*del)(void *));

t_token		*lst_new_elem_token(char type, char *value);
t_token		*lst_last_token(t_token *lst);
void		lst_add_back_token(t_token **lst, t_token *new_node);
void		lst_delone_token(t_token *lst, void (*del)(void *));
void		lst_clear_token(t_token **lst, void (*del)(void *));

void		env_to_list(char **envp, t_var **env_lst);
int			parsing_line(char *line);
int			tokens_count(char *line, char *metachars);
void		tokens_array(char *line, char *metachars, t_token **tokens);
void		tokens_trim(t_token **tokens);

#endif
