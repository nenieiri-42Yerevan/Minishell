/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 20:39:41 by vismaily          #+#    #+#             */
/*   Updated: 2022/04/26 16:05:54 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dups(t_command *tmp)
{
	if (tmp->pipe_in != 0)
	{
		tmp->std_in_dup1 = dup(0);
		dup2(tmp->pipe_in, 0);
		close(tmp->pipe_in);
		if (tmp->std_in != 0)
			close(tmp->std_in);
	}
	else if (tmp->std_in != 0)
	{
		tmp->std_in_dup1 = dup(0);
		dup2(tmp->std_in, 0);
		close(tmp->std_in);
	}
	if (tmp->std_out != 1)
	{
		tmp->std_out_dup1 = dup(1);
		dup2(tmp->std_out, 1);
		close(tmp->std_out);
		if (tmp->pipe_out != 0)
			close(tmp->pipe_out);
	}
	else if (tmp->pipe_out != 0)
	{
		tmp->std_out_dup1 = dup(1);
		dup2(tmp->pipe_out, 1);
		close(tmp->pipe_out);
	}
}
