/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:27 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/09 21:18:34 by lpeggy           ###   ########.fr       */
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
	(void)signal;
	write(1, "\n", 1);
	write(1, "sigint recieved\n", 16);
}

/*
static void		sigquit_handler(int signal)
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

static void	free_array(char **arr)
{
	int		i;

	i = -1;
	if (arr)
	{
		while (arr[i])
			free(arr[i]);
	}
}

t_list	*copy_envp(t_list *env, char **envp)
{
	int		i;

	// make it a list with key & value
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
	//t_env		*env;
	t_list	*env = NULL;
	char	**args;

	(void)argc;
	(void)argv;
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		exit_failure("");
//	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
//		exit_failure("");

	//char	*arr[] = {"p1", "p2", NULL};
	env = copy_envp(env, envp);
/*	while (1)
	{
		write(1, "assh:> ", 7);
		args = read_input();//
		execute(args, env);
		//args++;
		//del lst cmd and args and move next
		//free();
		free_array(args);
	}
	*/
	char	*line;

	while ((line = readline("assh:> ")) != NULL)
	{
		args = ft_split(line, ' ');
		//parse
		execute(args, env);
		if (ft_strlen(line) > 0)
				add_history(line);//clean after?
	}
	free(line);
	return (0);
	//return (EXIT_SUCCESS);
}
