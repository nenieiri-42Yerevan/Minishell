/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:14:31 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/23 17:25:48 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	intra(void)
{
	printf("***************************************************************\n");
	printf("*  .-.   .-..-..-. .-..-.    .----..-. .-..----..-.   .-.     *\n");
	printf("*  |  `.'  || ||  `| || |   { {__  | {_} || {_  | |   | |     *\n");
	printf("*  | |╲ /| || || |╲  || |   .-._} }| { } || {__ | `--.| `--.  *\n");
	printf("*  `-' ` `-'`-'`-' `-'`-'   `----' `-' `-'`----'`----'`----'  *\n");
	printf("***************************************************************\n");
	printf("*        :::      :::::::: ***   Author: Volodya Ismailyan    *\n");
	printf("*      :+:      :+:    :+: ***   E-Mail: nenie_iri@mail.ru    *\n");
	printf("*    +:+ +:+         +:+   ************************************\n");
	printf("*  +#+  +:+       +#+      ***    ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★     *\n");
	printf("*+#+#+#+#+#+   +#+         ************************************\n");
	printf("*     #+#    #+#           ***  Updated: 2022/04/12 12:46:50  *\n");
	printf("*    ###   ########.fr     ***  Created: 2022/03/26 16:14:31  *\n");
	printf("***************************************************************\n");
}

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
	intra();
	env_to_list(envp, &env_lst);
	while (1)
	{
		line = readline("Minishell$ ");
		parsing_line(line, &tokens, &env_lst);
		free(line);
	}
	lst_clear(&env_lst, free);
	return (0);
}
