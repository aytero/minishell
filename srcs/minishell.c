/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:27 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/05 19:08:00 by lpeggy           ###   ########.fr       */
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

static void	sigquit_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	write(1, "sigquit recieved\n", 16);
	exit(0);
}

void	free_memory(t_vars *vars)
{
	//ft_lstclear(args);
	free_double_array(vars->env);
	free_double_array(vars->path_arr);
	free(vars->path);
	//write(1, "emm\n", 4);
	//sleep(10);
}

static void	init_sh(t_vars *vars, char **envp)
{
	ft_memset(vars, 0, sizeof(t_vars));
	g_exit_status = 0;
	vars->env = copy_env_arr(envp, vars);
	vars->path = ft_strdup(getenv("PATH"));
	vars->path_arr = ft_split(vars->path, ':');
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	char	*line;

	(void)argv;
	argc == 1 || exit_failure("Too many arguments", 0);
	init_sh(&vars, envp);
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		exit_failure("Signal failure", 1);
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
		exit_failure("Signal failure", 1);

	while ((line = readline("assh:> ")) != NULL)
	{
		errno = 0;
		vars.args = ft_split(line, ' ');
		//parse(&vars);
		execute(&vars);
		if (ft_strlen(line) > 0)
				add_history(line);//clean after?
		free(line);
		free_double_array(vars.args);
	}
	free(line);
	free_memory(&vars);
	return (0);
}
