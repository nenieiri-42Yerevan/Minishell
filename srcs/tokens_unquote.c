/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_unquote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:11:34 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/10 20:41:24 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	double_quote(char *str, int *i, t_var *env_lst)
{
	char	*new_str;
	int		j;

	str[*i] = '\0';
	new_str = ft_strjoin(str, str + *i + 1);
	free(str);
	str = new_str;
	j = *i;
	while (str[j] != '\"')
	{
		if (str[j] == '$')
		{
			expansion(str, i, env_lst);
			printf("AAA %d\n", j);
		}
		j++;
	}
	str[j] = '\0';
	new_str = ft_strjoin(str, str + j + 1);
	free(str);
	str = new_str;
	*i = j - 1;
}

static void	single_quote(char *str, int *i)
{
	char	*new_str;
	int		j;

	str[*i] = '\0';
	new_str = ft_strjoin(str, str + *i + 1);
	free(str);
	str = new_str;
	j = *i;
	while (str[j] != '\'')
		j++;
	str[j] = '\0';
	new_str = ft_strjoin(str, str + j + 1);
	free(str);
	str = new_str;
	*i = j - 1;
}
*/
static int	my_replace(t_token *tokens, int i, int j, t_var *env_lst)
{
	char	*new_value;
	char	*new_blank;
	char	*new_str;

	new_value = ft_strdup(env_lst->value);
	tokens->value[i] = '\0';
	new_str = ft_strjoin(tokens->value, new_value);
	free(new_value);
	new_value = ft_strjoin(new_str, tokens->value + j);
	free(new_str);
	free(tokens->value);
	tokens->value = new_value;
	new_blank = (char *)malloc(sizeof(char) * (ft_strlen(env_lst->value) + 1));
	if (new_blank == 0)
		return (-1);
	new_blank[ft_strlen(env_lst->value)] = '\0';
	ft_memset(new_blank, '0', ft_strlen(env_lst->value));
	tokens->quote[i] = '\0';
	new_str = ft_strjoin(tokens->quote, new_blank);
	free(new_blank);
	new_blank = ft_strjoin(new_str, tokens->quote + j);
	free(new_str);
	free(tokens->quote);
	tokens->quote = new_blank;
	return (0);
}

static void	search_and_replace(t_token *tokens, int i, t_var *env_lst)
{
	char	*new_str;
	int		j;

	j = i;
	while (tokens->value[j] != ' ' && tokens->value[j] != '\0' && \
			tokens->value[j] != '\t' && tokens->value[j] != '\"' && \
			tokens->value[j] != '\'')
		j++;
	new_str = ft_substr(tokens->value, i + 1, j - i - 1);
	while (env_lst != 0)
	{
		if (ft_strncmp(env_lst->name, new_str, ft_strlen(new_str) + 1) == 0)
			break ;
		env_lst = env_lst->next;
	}
	if (env_lst != 0)
		my_replace(tokens, i, j, env_lst);
	free(new_str);
}

static void	expansion(t_token *tokens, t_var *env_lst)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (tokens->value[++i] != '\0')
	{
		if (tokens->value[i] == '\'')
			while (tokens->value[i] != '\'')
				i++;
		else if (tokens->value[i] == '\"')
		{
			while (tokens->value[i] != '\"')
			{
				if (tokens->value[i] == '$')
					search_and_replace(tokens, i, env_lst);
				i++;
			}
		}
		else if (tokens->value[i] == '$')
			search_and_replace(tokens, i, env_lst);
	}
}

void	tokens_unquote(t_token *tokens, t_var *env_lst)
{
	t_token	*tmp;
	int		i;

	i = -1;
	tmp = tokens;
	while (tmp != 0)
	{
		while (tmp->value[++i] != '\0')
		{
			if (tmp->value[i] == '\'' || tmp->value[i] == '\"')
				tmp->quote[i] = '1';
			else
				tmp->quote[i] = '0';
		}
		tmp = tmp->next;
	}
	expansion(tokens, env_lst);
}
