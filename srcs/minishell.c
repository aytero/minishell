/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:27 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/03 21:55:37 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parser.h"

static void	reset_vars(t_vars *vars)
{
	g_exit_status = 0;
	errno = 0;
	vars->parse_err = 0;
	vars->flag_pipe = 0;
	vars->cmd_nbr = 0;
	vars->pipe_nbr = 0;
}

static int	init_sh(t_vars *vars, char **envp)
{
	char	*path;
	char	*tmp;

	tmp = ft_strdup("OLDPWD");
	ft_memset(vars, 0, sizeof(t_vars));
	g_exit_status = 0;
	errno = 0;
	vars->env = env_to_list(envp);
	delete_env_var(&vars->env, tmp);
	free(tmp);
	path = get_env_var(vars->env, "PATH");
	path && (vars->path_arr = ft_split(path, ':'));
	!path && (vars->path_arr = ft_calloc(sizeof(char *), 1));
	if (!vars->path_arr)
		return (0);
	return (1);
}

static int	deal_eof(t_vars *vars, char *line)
{
	write(2, "exit\n", 5);
	free(line);
	free_mem(vars);
	rl_clear_history();
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	char	*line;

	(void)argv;
	if (argc > 1)
		return (!write(1, "Too many arguments\n", 19));
	init_sh(&vars, envp) || exit_failure("malloc fatal", NULL, 1);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	line = readline("sh:> ");
	!line && deal_eof(&vars, line);
	while (line != NULL)
	{
		(ft_strlen(line) > 0) && add_history(line);
		reset_vars(&vars);
		pre_parser(line, &vars);
		execute(&vars);
		free(line);
		ft_lstclear(&vars.cmd_arr, free_proc);
		line = readline("sh:> ");
		!line && deal_eof(&vars, line);
	}
	return (0);
}
