/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:23:05 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/09 23:29:40 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
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

typedef struct s_command
{
	char				**args;
	char				*oper;
	char				*oper_value;
	int					std_in;
	int					std_out;
	struct s_command	*next;
	t_token				*balance;
}						t_command;

t_var		*lst_new_elem(char *name, char *value);
t_var		*lst_last(t_var *lst);
void		lst_add_back(t_var **lst, t_var *new_node);
void		lst_delone(t_var *lst, void (*del)(void *));
void		lst_clear(t_var **lst, void (*del)(void *));
int			lst_size(t_var *lst);

t_token		*lst_new_elem_token(char type, char *value);
t_token		*lst_last_token(t_token *lst);
void		lst_add_back_token(t_token **lst, t_token *new_node);
void		lst_delone_token(t_token *lst, void (*del)(void *));
void		lst_clear_token(t_token **lst, void (*del)(void *));
int			lst_size_token(t_token *lst);

void		env_to_list(char **envp, t_var **env_lst);
char		**env_lst_to_arr(t_var *env_lst);
char		*strjoin_base(char const *s1, char const *s2, char c);
void		arr_free(char **arr);

int			parsing_line(char *line, t_token **tokens, t_var **env_lst);
int			tokens_count(char *line, char *metachars);
void		tokens_array(char *line, char *metachars, t_token **tokens, \
			t_var *env_lst);
void		tokens_trim(t_token **tokens);
void		tokens_unquote(t_token *tokens, t_var *env_lst);
void		parsing_command(t_token **tokens, t_command **command);

void		exec(t_command *command, t_token **tokens, t_var **env_lst);

#endif
