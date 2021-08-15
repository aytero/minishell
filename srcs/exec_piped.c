/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 18:24:09 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/15 20:10:20 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	close_pipes(t_vars *vars)
{
	int		i;

	i = -1;
	while (++i < vars->pipe_nbr)
	{
		close(vars->pfd[i][0]);
		close(vars->pfd[i][1]);
	}
	free_double_int_arr(vars->pfd, vars->pipe_nbr);
	return (1);
}

static void	open_pipes(t_vars *vars, t_proc *proc)
{
	int		i;

	vars->pfd = malloc(sizeof(int *) * vars->pipe_nbr);
	vars->pfd || exit_failure(proc->cmd, NULL, 0);
	i = -1;
	while (++i < vars->pipe_nbr)
	{
		vars->pfd[i] = malloc(sizeof(int) * 2);
		vars->pfd[i] || exit_failure(proc->cmd, NULL, 0);
	}
	i = -1;
	while (++i < vars->pipe_nbr)
		pipe(vars->pfd[i]);
}

int	deal_pipes(t_vars *vars, t_proc *proc)
{
	if (proc->id != 0)
		dup2(vars->pfd[proc->id - 1][0], 0) >= 0
		|| exit_failure(proc->cmd, NULL, 1);
	if (proc->id != vars->pipe_nbr)
		dup2(vars->pfd[proc->id][1], 1) >= 0
		|| exit_failure(proc->cmd, NULL, 1);
	return (1);
}

static void	pipe_child_proc(t_proc *proc, t_vars *vars, int i)
{
	proc->id = i;
	choose_cmd(proc, vars);
	exit(g_exit_status);
}

void	exec_piped(t_vars *vars)
{
	int		i;
	t_list	*tmp;
	t_proc	*proc;

	open_pipes(vars, (t_proc *)vars->cmd_arr->content);
	i = 0;
	tmp = vars->cmd_arr;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (tmp)
	{
		proc = (t_proc *)tmp->content;
		proc->pid = fork();
		proc->pid >= 0 || report_failure(proc->cmd, NULL, 0);
		if (proc->pid == 0)
			pipe_child_proc(proc, vars, i);
		tmp = tmp->next;
		i++;
	}
	close_pipes(vars);
	ft_lstiter(vars->cmd_arr, &wait_loop);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
