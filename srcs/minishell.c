/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:27 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/15 23:12:21 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#include "execute.h"
#include "parser.h"

static void	sig_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	write(1, "sigint recieved\n", 16);
}

/*
static void	sigquit_handler(int signal)
{
	exit(0);
}
*/

/*
void	free_mem()
{
	ft_lstclear(args);
}
*/

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	char	*line;

	g_exit_status = 0;
	(void)argv;
	if (argc > 1)
	{
		write(1, "Too many arguments\n", 19);
		return (0);
	}
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		exit_failure("Signal failure");
//	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
//		exit_failure("");

	vars.env = copy_envp(envp, &vars);
	while ((line = readline("assh:> ")) != NULL)
	{
		vars.args = ft_split(line, ' ');
		//parse(&vars);
		execute(&vars);
		if (ft_strlen(line) > 0)
				add_history(line);//clean after?
	}
	free(line);
	return (0);
	//return (EXIT_SUCCESS);
}
