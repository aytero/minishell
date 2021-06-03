/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:27 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/03 20:52:22 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#include "execute.h"

static void		sighandler(int signal)
{
	write(1, "sigint recieved\n", 16);
}

int		main(int argc, char **argv, char **envp)
{
	//char	**args;
	char	*args[] = {"pwd", "exec_test", "arg", NULL};

	if (signal(SIGINT, sighandler) == SIG_ERR)
		exit_failure("");
		//exit(EXIT_FAILURE);
	while (1)
	{
		write(1, "assh:> ", 7);
		//args = parse_input();//
		execute(args, envp);
		//args++;
		//free(args);
		//free();
		sleep(3);
	}
	return (0);
	//return (EXIT_SUCCESS);
}
