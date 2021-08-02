/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:49:41 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/02 21:48:39 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	if_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (2);
	if (!ft_strcmp(cmd, "pwd"))
		return (3);
	if (!ft_strcmp(cmd, "export"))
		return (4);
	if (!ft_strcmp(cmd, "unset"))
		return (5);
	if (!ft_strcmp(cmd, "env"))
		return (6);
	if (!ft_strcmp(cmd, "exit"))
		return (7);
	return (0);
}

int	choose_cmd(t_proc *proc, t_vars *vars)
{
	int		i;

	DEBUG && printf(GREY"choosing cmd"RESET);
	i = if_builtin(proc->cmd);
	if (i)
	{
		DEBUG && printf(GREY"executing builtin cmd"RESET);
		if ((proc->flag_redir && !vars->flag_pipe) && !deal_redir(proc))
			return (g_exit_status);
		if (vars->flag_pipe)
			deal_pipes(vars, proc);
		if (proc->rd_in_nbr && (dup2(proc->fd[FD_IN], 0) < 0))
			return (report_failure(proc->infiles[proc->rd_in_nbr - 1],
					NULL, 1));
		if (proc->rd_out_nbr && (dup2(proc->fd[FD_OUT], 1) < 0))
			return (report_failure(proc->outfiles[proc->rd_out_nbr - 1],
					NULL, 1));
		i == 1 && builtin_echo(proc->args);
		i == 2 && builtin_cd(proc->args, vars);
		i == 3 && builtin_pwd(vars);
		i == 4 && builtin_export(proc->cmd, proc->args, vars);
		i == 5 && builtin_unset(proc->cmd, proc->args, vars);
		i == 6 && builtin_env(proc, &vars->env);
		i == 7 && builtin_exit(proc->args, vars);
		return (g_exit_status);
	}
	return (exec_extern(proc, vars));
}

static int	restore_stdio(t_vars *vars)
{
	if (dup2(vars->fd_holder[FD_IN], 0) < 0)
		return (!report_failure("dup2", NULL, 1));
	if (dup2(vars->fd_holder[FD_OUT], 1) < 0)
		return (!report_failure("dup", NULL, 1));
	return (1);
}

static int	store_stdio(t_vars *vars)
{
	vars->fd_holder[FD_IN] = dup(0);
	if (vars->fd_holder[FD_IN] < 0)
		return (!report_failure("dup", NULL, 1));
	vars->fd_holder[FD_OUT] = dup(1);
	if (vars->fd_holder[FD_OUT] < 0)
		return (!report_failure("dup", NULL, 1));
	return (1);
}

void	execute(t_vars *vars)
{
	t_proc	*proc;

	if (!store_stdio(vars) || vars->parse_err)
		return ;
	proc = (t_proc *)vars->cmd_arr->content;
	if (!proc->cmd)
	{
		deal_redir(proc);
		restore_stdio(vars);
		DEBUG && printf(GREY"exit status: %d"RESET, g_exit_status);
		return ;
	}
	DEBUG && printf(GREY"\tstarting execution"RESET);
	if (vars->flag_pipe)
		exec_piped(vars);
	else
		choose_cmd(proc, vars);
	restore_stdio(vars);
	DEBUG && printf(GREY"exit status: %d"RESET, g_exit_status);
}
