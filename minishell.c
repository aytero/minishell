/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:27 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/07 23:44:51 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#include "execute.h"
#include "parser.h"

static void		sig_handler(int signal)
{
	write(1, "\n", 1);
	write(1, "sigint recieved\n", 16);
}

/*
void	free_mem()
{
	ft_lstclear(args);
}
*/

t_list	*copy_envp(t_list *env, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&env, ft_lstnew(envp[i]));
		i++;
	}
	return (env);
}

int		main(int argc, char **argv, char **envp)
{
	//t_args	*args;

	t_list	*env;
	char	**args;

	if (signal(SIGINT, sig_handler) == SIG_ERR)
		exit_failure("");
	//if (signal(SIGQUIT, sig_handler) == SIG_ERR)
	//	exit_failure("");

	env = copy_envp(env, envp);
	while (1)
	{
		write(1, "assh:> ", 7);
		args = read_input();//
		execute(args, env);
		//args++;
		//del lst cmd and args and move next
		//free();
	}
	return (0);
	//return (EXIT_SUCCESS);
}
