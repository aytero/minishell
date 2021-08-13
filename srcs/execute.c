/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:49:41 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/13 22:43:52 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	restore_stdio(t_vars *vars, int io)
{
	if (io == 0)
	{
		if (dup2(vars->fd_holder[FD_IN], 0) < 0)
			return (!report_failure("dup2", NULL, 0));
		close(vars->fd_holder[FD_IN]);
	}
	else if (io == 1)
	{
		if (dup2(vars->fd_holder[FD_OUT], 1) < 0)
			return (!report_failure("dup", NULL, 0));
		close(vars->fd_holder[FD_OUT]);
	}
	return (1);
}

int	store_stdio(t_vars *vars, int io)
{
	if (io == 0)
	{
		vars->fd_holder[FD_IN] = dup(0);
		close(0);
		if (vars->fd_holder[FD_IN] < 0)
			return (!report_failure("dup", NULL, 0));
	}
	if (io == 1)
	{
		vars->fd_holder[FD_OUT] = dup(1);
		if (vars->fd_holder[FD_OUT] < 0)
			return (!report_failure("dup", NULL, 0));
		close(1);
	}
	return (1);
}

static int	if_builtin(char *cmd)
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

	if (!proc->cmd)
	{
		deal_redir(proc);
		return (g_exit_status);
	}
	i = if_builtin(proc->cmd);
	if (!i)
		return (exec_extern(proc, vars));
	exec_builtin(vars, proc, i);
	return (g_exit_status);
}

void	execute(t_vars *vars)
{
	t_proc	*proc;

	if (vars->parse_err)
		return ;
	proc = (t_proc *)vars->cmd_arr->content;
	if (vars->flag_pipe)
		exec_piped(vars);
	else
		choose_cmd(proc, vars);
}
