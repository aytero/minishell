/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 18:24:09 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/13 23:08:34 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	close_pipes(t_vars *vars)
{
	int		i;

	i = -1;
	while (++i < vars->pipe_nbr)
	{
		close(vars->pfd[i][0]);
		close(vars->pfd[i][1]);
	}
	//free_double_int_array(vars->pfd);
}

void	open_pipes(t_vars *vars)
{
	int		i;

	//malloc_ptr
	vars->pfd = malloc(sizeof(int *) * vars->pipe_nbr);
	vars->pfd || exit_failure("malloc", 1);
	i = -1;
	while (++i < vars->pipe_nbr)
	{
		vars->pfd[i] = malloc(sizeof(int) * 2);
		vars->pfd[i] || exit_failure("malloc", 1);
	}
	i = -1;
	while (++i < vars->pipe_nbr)
		pipe(vars->pfd[i]);
}

void	deal_pipes(t_vars *vars, int i)
{
	if (i == 0)
	{
		close(vars->pfd[i][0]);
		dup2(vars->pfd[i][1], 1) >= 0 || exit_failure("dup2", 1);
		close(vars->pfd[i][1]);
	}
	else if (i == vars->pipe_nbr)
	{
		close(vars->pfd[i - 1][1]);
		dup2(vars->pfd[i - 1][0], 0) >= 0 || exit_failure("dup2", 1);
		close(vars->pfd[i - 1][0]);
	}
	/*
	else
	{
		//dup2(vars->pfd[i][0], 0) >= 0 || exit_failure("dup2", 1);
		close(vars->pfd[i][0]);
		dup2(vars->pfd[i][1], 1) >= 0 || exit_failure("dup2", 1);
		close(vars->pfd[i][1]);
	}
	*/

	/*
	if (i == vars->pipe_nbr)//last cmd
	{
		close(vars->pfd[i - 1][1]);
		dup2(vars->pfd[i - 1][0], 0) >= 0 || exit_failure("dup2", 1);
		close(vars->pfd[i - 1][0]);
	}
	else
	{
		//dup2(vars->pfd[i - 1][0], 0);
		close(vars->pfd[i][0]);
		dup2(vars->pfd[i][1], 1) >= 0 || exit_failure("dup2", 1);
		close(vars->pfd[i][1]);
	}
	*/
}

/*
void	pipe_loop(t_vars *vars)//, char **argv)
{
	int		i;
	pid_t	pid;
	char	**args;

	i = -1;
	while (++i < vars->cmd_nbr)
	{
		args = ft_split(argv[i + 2], ' ');// null at the end??
		args[0] = find_cmd_path(vars->path_arr, args[0]);
		//args[0] || exit_failure("path", 0);
		pid = fork();
		pid >= 0 || exit_failure("fork", 1);
		if (pid == 0)
		{
			deal_pipes(vars, i);
			execve(args[0], args, vars->env) >= 0 || exit_failure("execve", 1);
			exit(0);
		}
		else
			free_double_array(args);
	}
	while (waitpid(0, 0, 0) <= 0)
		;
}
*/

/*
int	exec_piped(char *cmd, t_vars *vars)
{
	int		i;
	pid_t	pid;

	open_pipes(vars);
	i = -1;
	while (++i < vars->cmd_nbr)
	{
		pid = fork();
		pid >= 0 || exit_failure("fork", 1);
		if (pid == 0)
		{
			deal_pipes(vars, i);
			choose_cmd(cmd, vars);
			exit(0);
		}
	}
	wait_loop(pid);
	//while (waitpid(0, 0, 0) <= 0)
	//	;
	close_pipes(vars);
	return (0);
}
*/
