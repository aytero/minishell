/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:27 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/15 23:32:42 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	free_double_array(void *ptr)
{
	int		i;
	char	**arr;

	arr = ptr;
	i = -1;
	if (arr)
	{
		while (arr[++i])
		{
			if (arr[i])
				free(arr[i]);
		}
		free(arr);
	}
}

void	free_memory(t_vars *vars)
{
	//ft_lstclear(vars->cmd_arr);
	//free_double_array(vars->env);
	free_double_array(vars->path_arr);
	//free(vars->path);
	//write(1, "emm\n", 4);
	//sleep(10);
}

static void	init_sh(t_vars *vars, char **envp)
{
	ft_memset(vars, 0, sizeof(t_vars));
	g_exit_status = 0;
	//vars->env = copy_env_arr(envp, vars);
	vars->env = env_to_list(envp);
	//set_env_var(&vars->env, "OLDPWD");//makes it kinda invisible
	//vars->path = ft_strdup(getenv("PATH"));//mb not useful
	vars->path = get_env_var(vars->env, "PATH");//mb not useful
	vars->path_arr = ft_split(vars->path, ':');
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	char	*line;

	(void)argv;//
	argc == 1 || exit_failure("Too many arguments", 0);
	init_sh(&vars, envp);
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		exit_failure("Signal failure", 1);
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
		exit_failure("Signal failure", 1);
	line = readline("sh:> ");
	while (line != NULL)
	{
		if (ft_strlen(line) > 0)
				add_history(line);
		errno = 0;
		pre_parser(line, &vars);
		execute(&vars);
		free(line);
		ft_lstclear(&vars.cmd_arr, free_double_array);
		line = readline("sh:> ");
	}
	free(line);
	free_memory(&vars);
	return (0);
}
