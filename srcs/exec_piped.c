/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 18:24:09 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/02 20:16:32 by lpeggy           ###   ########.fr       */
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

int	deal_pipes(t_vars *vars, t_proc *proc)
{
	if (proc->id != 0)
		//dup2(vars->pfd[proc->id - 1][0], proc->fd[FD_IN]) >= 0 || exit_failure(proc->cmd, NULL, 1);
		dup2(vars->pfd[proc->id - 1][0], 0) >= 0 || exit_failure(proc->cmd, NULL, 1);
	if (proc->id != vars->pipe_nbr)
		//dup2(vars->pfd[proc->id][1], proc->fd[FD_OUT]) >= 0 || exit_failure(proc->cmd, NULL, 1);
		dup2(vars->pfd[proc->id][1], 1) >= 0 || exit_failure(proc->cmd, NULL, 1);
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
	signal(SIGINT, parent_sig_handler);
	signal(SIGQUIT, parent_sig_handler);
	while (tmp)
	{
		proc = (t_proc *)tmp->content;
		proc->pid = fork();
		proc->pid >= 0 || report_failure(proc->cmd, NULL, 1);
		if (proc->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			/*
			if (proc->flag_redir)
			{
				if (!deal_redir(proc))
					exit(g_exit_status);
				//write(2, "here\n", 5);
			}
			*/
			//lags when heredoc
			proc->id = i;
			//write(2, "err\n", 4);
			//deal_pipes(vars, proc) && close_pipes(vars);
			//close_pipes(vars);
			//write(2, "err\n", 4);
			choose_cmd(proc, vars);
			exit(g_exit_status);
			//exit(0);
		}
		tmp = tmp->next;
		i++;
	}
	close_pipes(vars);
	ft_lstiter(vars->cmd_arr, &wait_loop);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
