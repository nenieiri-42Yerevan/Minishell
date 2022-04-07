/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:14:31 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/06 15:14:49 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_var	*env_lst;
	t_token	*tokens;

	(void)argv;
	if (argc > 1)
	{
		printf("The program no needs to arguments\n");
		return (0);
	}
	env_to_list(envp, &env_lst);
	while (1)
	{
		line = readline("Minishell$ ");
		parsing_line(line, &tokens);
		free(line);
	}
	lst_clear(&env_lst, free);
	return (0);
}
