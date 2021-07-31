/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 18:24:09 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/31 20:20:08 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	free_double_int_array(int **arr, int size)
{
	int		i;

	i = -1;
	if (arr)
	{
		while (++i < size)
		{
			if (arr[i])
				free(arr[i]);
		}
		free(arr);
	}
}

void	close_pipes(t_vars *vars)
{
	int		i;

	i = -1;
	while (++i < vars->pipe_nbr)
	{
		close(vars->pfd[i][0]);
		close(vars->pfd[i][1]);
	}
	free_double_int_array(vars->pfd, vars->pipe_nbr);
}

void	open_pipes(t_vars *vars)
{
	int		i;

	vars->pfd = malloc(sizeof(int *) * vars->pipe_nbr);
	vars->pfd || exit_failure(NULL, "malloc", 1);
	i = -1;
	while (++i < vars->pipe_nbr)
	{
		vars->pfd[i] = malloc(sizeof(int) * 2);
		vars->pfd[i] || exit_failure(NULL, "malloc", 1);
	}
	i = -1;
	while (++i < vars->pipe_nbr)
		pipe(vars->pfd[i]);
}

void	deal_pipes(t_vars *vars, int i)
{
	//i != 0 && (dup2(vars->pfd[i - 1][0], 0) >= 0 || exit_failure("dup2", 1));
	//i != vars->pipe_nbr && (dup2(vars->pfd[i][1], 1) >= 0 || exit_failure("dup2", 1));
	if (i != 0)
		dup2(vars->pfd[i - 1][0], 0) >= 0 || exit_failure(NULL, "dup2", 1);
	if (i != vars->pipe_nbr)
		dup2(vars->pfd[i][1], 1) >= 0 || exit_failure(NULL, "dup2", 1);
}

int	exec_piped(t_vars *vars)
{
	int		i;
	t_list	*tmp;
	t_proc	*proc;

	DEBUG && printf(GREY"executing piped"RESET);
	open_pipes(vars);
	i = 0;
	tmp = vars->cmd_arr;
	while (tmp)
	{
		proc = (t_proc *)tmp->content;
		proc->pid = fork();
		proc->pid >= 0 || report_failure(NULL, "fork", 1);
		if (proc->pid == 0)
		{
			if (proc->flag_redir)
				deal_redir(proc) || exit_failure(NULL, "redir", 0);
			deal_pipes(vars, i);
			close_pipes(vars);
			choose_cmd(proc, vars);
			exit(0);
		}
		tmp = tmp->next;
		i++;
	}
	close_pipes(vars);
	ft_lstiter(vars->cmd_arr, &wait_loop);
	return (0);
}
