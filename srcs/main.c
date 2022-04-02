/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:14:31 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/02 18:46:38 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_var	**env_lst;

	(void)argv;
	if (argc > 1)
	{
		printf("The program no needs to arguments\n");
		return (0);
	}
	env_lst = env_to_list(envp);
	while (1)
	{
		line = readline("Minishell$ ");
		parsing_line(line);
		free(line);
	}
	return (0);
}
