/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:49:41 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/29 23:27:23 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	wait_loop(pid_t pid)
{		
	int		status;
	int		wpid;

	wpid = waitpid(pid, &status, 0);//WUNTRACED);
//	while (!WIFEXITED(status) && !WIFSIGNALED(status))
//		wpid = waitpid(pid, &status, WUNTRACED);

	if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
		//printf("exit status: %d\n", g_exit_status);
	}
//	if (waitpid(pid, &status, WUNTRACED | WCONTINUED) == -1)
//		exit_failure("");
}

int	exec_piped(t_vars *vars)
{
	int		i;
	pid_t	pid;
	t_list	*tmp;

	DEBUG && printf(GREY"executing piped"RESET);
	open_pipes(vars);
	i = 0;
	tmp = vars->cmd_arr;
	while (tmp)
	{
		pid = fork();
		pid >= 0 || report_failure(NULL, "fork", 1);
		if (pid == 0)
		{
			if (((t_proc *)tmp->content)->flag_redir)
				_deal_redir((t_proc *)tmp->content);
			deal_pipes(vars, i);
			close_pipes(vars);
			choose_cmd((t_proc *)tmp->content, vars);
			exit(0);
		}
		tmp = tmp->next;
		i++;
	}
	close_pipes(vars);

	int		status;
	int		wpid;

	wpid = waitpid(pid, &status, 0);//WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		wpid = waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	//wait_loop(vars->pid);
	return (0);
}

int	deal_here_doc(t_proc *proc, int i)
{
	int		fd;
	char	*str;

	fd = -1;
	fd = open("hd_buf", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	(fd >= 0) || report_failure(NULL, "open", 1);//return

	str = readline("> ");
	while (str != NULL && ft_strcmp(str, proc->infiles[i]))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	free(str);
	close(fd);
	return (1);
}

int	_deal_redir(t_proc *proc)
{
	int		fd;
	int		i;
	int		flags[4];

	flags[0] = O_RDONLY;
	flags[1] = O_WRONLY | O_TRUNC | O_CREAT;
	flags[2] = -1;
	flags[3] = O_WRONLY | O_APPEND | O_CREAT;
	fd = -1;
	i = -1;
	while (++i < proc->rd_in_nbr)
	{
		if (proc->rd_in_type[i] == 2)
		{
			deal_here_doc(proc, i);
			continue ;
		}
		fd = open(proc->infiles[i], flags[proc->rd_in_type[i]], 0644);
		(fd >= 0) || report_failure(NULL, "open", 1);//return
		dup2(fd, proc->fd[FD_IN]) >= 0 || report_failure(NULL, "dup2", 1);
		close(fd);
	}
	i = -1;
	while (++i < proc->rd_out_nbr)
	{
		fd = open(proc->outfiles[i], flags[proc->rd_out_type[i]], 0644);
		(fd >= 0) || report_failure(NULL, "open", 1);//return
		dup2(fd, proc->fd[FD_OUT]) >= 0 || report_failure(NULL, "dup2", 1);
		close(fd);
	}
	if (proc->flag_heredoc)
	{
		fd = open("hd_buf", O_RDONLY);
		(fd >= 0) || report_failure(NULL, "open", 1);//return
		dup2(fd, proc->fd[FD_IN]) >= 0 || report_failure(NULL, "dup2", 1);
		close(fd);
		//if signal hd_buf remains
		!unlink("hd_buf") || report_failure(NULL, "unlink", 1);
	}
	return (1);
}

int		_exec_extern(t_proc *proc, t_vars *vars)
{
	pid_t	pid;
	char	*path;

	DEBUG && printf(GREY"executing extern prog"RESET);

	pid = fork();
	//signal(SIGINT, );
	if (pid == -1)
		//return (report_failure("fork"));//though wouldnt be able to use ||
		return (report_failure(NULL, "fork", 1));
	if (pid == 0)
	{
		//printf(RED"type redir %d\n"RESET, ((t_proc *)(vars->cmd_arr)->content)->type_redir);

		//not working with pipes
		if (proc->flag_redir && !vars->flag_pipe)
			_deal_redir(proc);

		path = pathfinder(vars, proc->cmd);//if err exit status goes on same line with prompt
		DEBUG && printf(GREY"path = |%s|"RESET, path);
		//path || exit_failure("No such file or directory", 0);
		if (!path)
			return (report_failure(proc->args[0], "command not found", 0));

		if (proc->rd_in_nbr)
			dup2(proc->fd[FD_IN], 0) >= 0 || report_failure(NULL, "dup2", 1);
		if (proc->rd_out_nbr)
			dup2(proc->fd[FD_OUT], 1) >= 0 || report_failure(NULL, "dup2", 1);

		//printf(RED"emm"RESET);

		(execve(path, proc->args, env_to_char(vars->env)) >= 0) || exit_failure("execve", 1);
		//free(path);//all mem free
		exit(0);// ?
	}
	else
	{
		wait_loop(pid);
		//free(path);
	}
	return (0);
}

int	exec_extern(t_proc *proc, t_vars *vars)
{
	//signal(SIGINT, );
	char	*path;

	DEBUG && printf(GREY"executing extern prog"RESET);
	path = pathfinder(vars, proc->cmd);
	DEBUG && printf(GREY"path = |%s|"RESET, path);
	//path || exit_failure("No such file or directory", 0);
	if (!path)
		return (report_failure(proc->args[0], "command not found", 0));
	(execve(path, proc->args, env_to_char(vars->env)) >= 0) || report_failure(NULL, "execve", 1);
		return (0);
}

int	choose_cmd(t_proc *proc, t_vars *vars)
{
	//pid_t	pid;
	
	DEBUG && printf(GREY"choosing cmd"RESET);
	//this version kills working with env and exit cause it's all in children processes
	/*
	pid = fork();
	if (pid == 0)
	{
		proc->flag_redir && _deal_redir(proc);
		//if (!_deal_redir(proc))
		//	return (1);
		if (!ft_strcmp(proc->cmd, "echo"))
			exit(builtin_echo(proc->args));
		if (!ft_strcmp(proc->cmd, "cd"))
			exit(builtin_cd(proc->args, vars));
		if (!ft_strcmp(proc->cmd, "pwd"))
			exit(builtin_pwd(vars));
		if (!ft_strcmp(proc->cmd, "export"))
			exit(builtin_export(proc->args, vars));
		if (!ft_strcmp(proc->cmd, "unset"))
			exit(builtin_unset(proc->args, vars));
		if (!ft_strcmp(proc->cmd, "env"))
			exit(builtin_env(&vars->env));
		if (!ft_strcmp(proc->cmd, "exit"))
			exit(builtin_exit(proc->args, vars));
		exit(exec_extern(proc, vars));
	}
	else
		wait_loop(pid);
	return (0);
	*/

	// builtins && redirects:
	// func to store and resotre fd
	// or fork those what write smth to output
	// ex. export without args

	if (!ft_strcmp(proc->cmd, "echo"))
		return (builtin_echo(proc->args));
	if (!ft_strcmp(proc->cmd, "cd"))
		return (builtin_cd(proc->args, vars));
	if (!ft_strcmp(proc->cmd, "pwd"))
		return (builtin_pwd(vars));
	if (!ft_strcmp(proc->cmd, "export"))
		return (builtin_export(proc->args, vars));
	if (!ft_strcmp(proc->cmd, "unset"))
		return (builtin_unset(proc->args, vars));
	if (!ft_strcmp(proc->cmd, "env"))
		return (builtin_env(proc, &vars->env));
	if (!ft_strcmp(proc->cmd, "exit"))
		return (builtin_exit(proc->args, vars));
	return (_exec_extern(proc, vars));
}

/*
int	restore_fd(t_vars *vars)
{
	dup2(0, vars->fd[FD_IN]);// || report_failure();
	dup2(1, vars->fd[FD_OUT]);// || report_failure();
	return (1);
}
*/

int	execute(t_vars *vars)
{
	//vars->flag_redirect = 0;
	//if (((t_proc *)vars->cmd_arr->content)->args[0] == NULL)
	//	return (0);
	if (vars->parse_err)
		return (0);
	DEBUG && printf(GREY"\tstarting execution"RESET);
	if (vars->flag_pipe)
	//if (vars->pipe_nbr > 0)
		exec_piped(vars);
	else
		choose_cmd((t_proc *)vars->cmd_arr->content, vars);
	//restore_fd(vars);
	DEBUG && printf(GREY"exit status: %d"RESET, g_exit_status);
	return (0);
}
