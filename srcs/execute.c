/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:49:41 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/31 20:21:49 by lpeggy           ###   ########.fr       */
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



int		exec_extern(t_proc *proc, t_vars *vars)
{
	pid_t	pid;
	char	*path;

	DEBUG && printf(GREY"executing extern prog"RESET);

	pid = fork();
	signal(SIGINT, child_sig_handler);
	signal(SIGQUIT, child_sig_handler);
	if (pid == -1)
		return (report_failure(NULL, "fork", 1));
	if (pid == 0)
	{
		if (proc->flag_redir && !vars->flag_pipe)
			deal_redir(proc) || exit_failure(NULL, NULL, 0);//
		if (!proc->cmd)
			exit(0);
		path = pathfinder(vars, proc->cmd);
		DEBUG && printf(GREY"path = |%s|"RESET, path);
		path || exit_failure(proc->cmd, "command not found", 0);
		//path || exit_failure("No such file or directory", 0);

		if (proc->rd_in_nbr)
			dup2(proc->fd[FD_IN], 0) >= 0 || exit_failure(NULL, "dup2", 1);
		if (proc->rd_out_nbr)
			dup2(proc->fd[FD_OUT], 1) >= 0 || exit_failure(NULL, "dup2", 1);

		(execve(path, proc->args, env_to_char(vars->env)) >= 0)
			|| exit_failure(NULL, "execve", 1);
		//free(path);//all mem free
		exit(0);
	}
	else
	{
		wait_loop(proc);
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
	}
	return (0);
}

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
		if (proc->flag_redir && !vars->flag_pipe)
		{
			if (!deal_redir(proc))
				return (0);//
		}
		if (proc->rd_in_nbr)
			dup2(proc->fd[FD_IN], 0) >= 0 || report_failure(NULL, "dup2", 1);//return
		if (proc->rd_out_nbr)
			dup2(proc->fd[FD_OUT], 1) >= 0 || report_failure(NULL, "dup2", 1);
		//return (exec_builtin(proc, vars, i));
		if (i == 1)
			return (builtin_echo(proc->args));
		if (i == 2)
			return (builtin_cd(proc->args, vars));
		if (i == 3)
			return (builtin_pwd(vars));
		if (i == 4)
			return (builtin_export(proc->args, vars));
		if (i == 5)
			return (builtin_unset(proc->args, vars));
		if (i == 6)
			return (builtin_env(proc, &vars->env));
		if (i == 7)
			return (builtin_exit(proc->args, vars));
	}
	return (exec_extern(proc, vars));
}

/*
int	restore_stdio(t_vars *vars)
{
	dup2(fd_holder[FD_IN], 0);// || report_failure();
	dup2(fd_holder[FD_OUT], 1);// || report_failure();
	return (1);
}
*/

int	execute(t_vars *vars)
{
	int		fd_holder[2];	

	fd_holder[FD_IN] = dup(0);
	fd_holder[FD_OUT] = dup(1);
	//vars->flag_redirect = 0;
	//if (((t_proc *)vars->cmd_arr->content)->args[0] == NULL)
	//	return (0);
	if (vars->parse_err)
		return (0);
	if (!((t_proc *)vars->cmd_arr->content)->cmd)
	{
		deal_redir((t_proc *)vars->cmd_arr->content);//err
		dup2(fd_holder[FD_IN], 0);// || report_failure();
		dup2(fd_holder[FD_OUT], 1);// || report_failure();
		return (0);
	}
	DEBUG && printf(GREY"\tstarting execution"RESET);
	if (vars->flag_pipe)
	//if (vars->pipe_nbr > 0)
		exec_piped(vars);
	else
		choose_cmd((t_proc *)vars->cmd_arr->content, vars);
	//restore_fd(vars);
	dup2(fd_holder[FD_IN], 0);// || report_failure();
	dup2(fd_holder[FD_OUT], 1);// || report_failure();
	DEBUG && printf(GREY"exit status: %d"RESET, g_exit_status);
	return (0);
}
