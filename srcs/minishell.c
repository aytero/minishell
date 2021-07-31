/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:27 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/31 20:22:52 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parser.h"



//if ctrl-D - exit shell and write "exit"
//rl_replace_line("exit", 0);
//but only when line is empty so maybe not use replace func

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

static void	free_proc(void *ptr)
{
	//free all redirs stuff
	//if (((t_proc *)ptr)->filename)
	//	free(((t_proc *)ptr)->filename);
	if (((t_proc *)ptr)->cmd)
		free(((t_proc *)ptr)->cmd);
	free_double_array(((t_proc *)ptr)->args);
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
	argc == 1 || exit_failure(NULL, "Too many arguments", 0);
	init_sh(&vars, envp);
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		exit_failure(NULL, "Signal failure", 1);
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		exit_failure(NULL, "Signal failure", 1);
	line = readline("sh:> ");
	if (!line)
	{
		write(2, "exit\n", 5);
		exit(0);
	}
	while (line != NULL)
	{
		(ft_strlen(line) > 0) && add_history(line);
		errno = 0;
		vars.parse_err = 0;
		pre_parser(line, &vars);
		execute(&vars);
		free(line);
		//ft_lstclear(&vars.cmd_arr, free_double_array);
		ft_lstclear(&vars.cmd_arr, free_proc);
		line = readline("sh:> ");
		if (!line)
		{
			//free mem
			write(2, "exit\n", 5);
			break ;
			//exit(0);
		}
	}
	//rl_clear_history();
	free(line);
	free_memory(&vars);
	return (0);
}
