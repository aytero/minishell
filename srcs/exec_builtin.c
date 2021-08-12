/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 19:58:30 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/12 22:03:38 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
	if (proc->rd_out_nbr)
	{
		if (dup2(proc->fd[FD_OUT], 1) < 0)
			return (report_failure(proc->outfiles[proc->rd_out_nbr - 1],
				NULL, 0));
		close(proc->fd[FD_OUT]);
	}
*/
int	exec_builtin(t_vars *vars, t_proc *proc, int cmd_id)
{
	if ((proc->flag_redir && !vars->flag_pipe) && !deal_redir(proc))
		return (g_exit_status);
	vars->flag_pipe && deal_pipes(vars, proc);
	if ((proc->rd_in_nbr || proc->rd_out_nbr) && !store_stdio(vars))
		return (g_exit_status);
	if (proc->rd_in_nbr && !(dup2(proc->fd[FD_IN], 0) >= 0
			&& !close(proc->fd[FD_IN])))
		return (report_failure(proc->infiles[proc->rd_in_nbr - 1],
				NULL, 0));
	if (proc->rd_out_nbr && !(dup2(proc->fd[FD_OUT], 1) >= 0
			&& !close(proc->fd[FD_OUT])))
		return (report_failure(proc->outfiles[proc->rd_out_nbr - 1],
				NULL, 0));
	cmd_id == 1 && builtin_echo(proc->args);
	cmd_id == 2 && builtin_cd(proc->args, vars);
	cmd_id == 3 && builtin_pwd(vars);
	cmd_id == 4 && builtin_export(proc->cmd, proc->args, vars);
	cmd_id == 5 && builtin_unset(proc->cmd, proc->args, vars);
	cmd_id == 6 && builtin_env(proc, &vars->env);
	cmd_id == 7 && builtin_exit(proc->args, vars);
	(proc->rd_in_nbr || proc->rd_out_nbr) && restore_stdio(vars);
	return (0);
}
