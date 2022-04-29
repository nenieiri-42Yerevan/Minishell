/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:00:30 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/29 11:42:12 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\b\b  \b\b\n", 7); 
	rl_on_new_line();
	rl_replace_line("", 0); 
	rl_redisplay();
}

static void	handle_sigquit(int sig)
{
	(void)sig;
	write(1, "\b\b  \b\b", 6); 
	rl_redisplay();
}

void	signals_init(struct s_signal *signals)
{
	signals = (struct s_signal *)malloc(sizeof(struct s_signal));
	signals->sa_quit.sa_handler = &handle_sigquit;
	signals->sa_int.sa_handler = &handle_sigint;	
	sigaction(SIGQUIT, &(signals->sa_quit), NULL);
	sigaction(SIGINT, &(signals->sa_int), NULL);
}
