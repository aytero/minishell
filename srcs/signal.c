/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 18:09:16 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/02 22:27:45 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	parent_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		g_exit_status = 130;
	}
	if (signal == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
		g_exit_status = 131;
	}
}

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		g_exit_status = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		write(2, "\r", 1);
		rl_on_new_line();
		rl_redisplay();
		exit(0);
	}
}
