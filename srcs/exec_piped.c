/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 18:24:09 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/01 20:36:28 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	close_pipes(t_vars *vars)
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
	vars->pfd || exit_failure(proc->cmd, NULL, 1);
	i = -1;
	while (++i < vars->pipe_nbr)
	{
		vars->pfd[i] = malloc(sizeof(int) * 2);
		vars->pfd[i] || exit_failure(proc->cmd, NULL, 1);
	}
	i = -1;
	while (++i < vars->pipe_nbr)
		pipe(vars->pfd[i]);
}

static int	deal_pipes(t_vars *vars, t_proc *proc, int i)
{
	if (i != 0)
		dup2(vars->pfd[i - 1][0], 0) >= 0 || exit_failure(proc->cmd, NULL, 1);
	if (i != vars->pipe_nbr)
		dup2(vars->pfd[i][1], 1) >= 0 || exit_failure(proc->cmd, NULL, 1);
	return (1);
}

void	exec_piped(t_vars *vars)
{
	int		i;
	t_list	*tmp;
	t_proc	*proc;

	DEBUG && printf(GREY"executing piped"RESET);
	open_pipes(vars, (t_proc *)vars->cmd_arr->content);
	i = 0;
	tmp = vars->cmd_arr;
	while (tmp)
	{
		proc = (t_proc *)tmp->content;
		proc->pid = fork();
		proc->pid >= 0 || report_failure(proc->cmd, NULL, 1);
		if (proc->pid == 0)
		{
			if (proc->flag_redir)
			{
				//deal_redir(proc) || exit_failure(proc->cmd, NULL, 0);
				if (!deal_redir(proc))
					exit(g_exit_status);
			}
			deal_pipes(vars, proc, i) && close_pipes(vars);
			choose_cmd(proc, vars);
			exit(0);
		}
		tmp = tmp->next;
		i++;
	}
	close_pipes(vars);
	ft_lstiter(vars->cmd_arr, &wait_loop);
}
