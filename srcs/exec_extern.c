/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 18:48:21 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/03 19:29:11 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	wait_loop(void *ptr)
{
	int		status;
	int		wpid;
	t_proc	*proc;

	proc = (t_proc *)ptr;
	wpid = waitpid(proc->pid, &status, 0);//WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		wpid = waitpid(proc->pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
//	if (waitpid(pid, &status, WUNTRACED | WCONTINUED) == -1)
//		exit_failure("");
}

static void	wait_one(pid_t pid)
{
	int		status;
	int		wpid;

	wpid = waitpid(pid, &status, 0);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		wpid = waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

static void	exec_child_proc(t_proc *proc, t_vars *vars)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if ((proc->flag_redir && !deal_redir(proc)) || !proc->cmd)
		exit(g_exit_status);
	if (vars->flag_pipe)
		deal_pipes(vars, proc) && close_pipes(vars);
	path = pathfinder(vars, proc->cmd);
	DEBUG && printf(GREY"path = |%s|"RESET, path);
	path || exit_failure(proc->cmd, "command not found", 0);
	if (proc->rd_in_nbr)
	{
		dup2(proc->fd[FD_IN], 0) >= 0 || exit_failure(proc->cmd, NULL, 1);
		close(proc->fd[FD_IN]);
	}
	if (proc->rd_out_nbr)
	{
		dup2(proc->fd[FD_OUT], 1) >= 0 || exit_failure(proc->cmd, NULL, 1);
		close(proc->fd[FD_OUT]);
	}
	(execve(path, proc->args, env_to_char(vars->env)) >= 0)
		|| exit_failure(proc->cmd, NULL, 1);
	free(path);
}

int	exec_extern(t_proc *proc, t_vars *vars)
{
	pid_t	pid;

	DEBUG && printf(GREY"executing extern prog"RESET);
	signal(SIGINT, parent_sig_handler);
	signal(SIGQUIT, parent_sig_handler);
	pid = fork();
	if (pid == -1)
		return (report_failure(proc->cmd, NULL, 1));
	if (pid == 0)
	{
		exec_child_proc(proc, vars);
		exit(0);
	}
	else
	{
		if (vars->flag_pipe)
		{
			close_pipes(vars);
			wait_one(pid);
		}
		else
			wait_loop(proc);
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
	}
	return (0);
}
