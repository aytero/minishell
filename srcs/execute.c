/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:49:41 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/29 20:57:32 by lpeggy           ###   ########.fr       */
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

/*
static int	exec_child_ps(t_vars *vars, pid_t pid, int io_flag)// int *fd, char *cmd)
{
	if (pid < 0)
		exit_failure("Fork error");
	if (pid == 0)
	{
		close(fd[!io_flag]);//0
		dup2(fd[io_flag], STDOUT_FILENO);//1
		close(fd[io_flag]);//1
		choose_cmd(cmd, vars);
		exit(0);
	}
}
*/

int	exec_piped(char *cmd, t_vars *vars)
{
	int	fd[2];
	pid_t	pid;
	pid_t	pid1;
//	int		wpid = 0;//pid_t ?

	if (pipe(fd) < 0)
		exit_failure("Pipe error");
	pid = fork();
	/*
	if (pid <= 0)
		exec_child_ps(pid, 1);
	else
	{
		pid1 = fork();
		if (pid1 <= 0)
			exec_child_ps(pid1, 0);
		else
		{
			wait_loop(pid);
			wait_loop(pid1);
			//close(fd[0]);
			//close(fd[1]);
		}
	}
*/

	if (pid < 0)
		exit_failure("Fork error");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		choose_cmd(cmd, vars);
		exit(0);
	}
	else
	{
		pid1 = fork();
		if (pid1 < 0)
			exit_failure("Fork error");
		if (pid1 == 0)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			choose_cmd(vars->args[1], vars);//args move is not automized
			exit(0);
		}
		else
		{
			wait_loop(pid);
			wait_loop(pid1);//TODO manage this so loop makes sense
			//wait(NULL);
			//wait(NULL);
			close(fd[0]);
			close(fd[1]);
		}
	}
	return (0);
}

int	exec_extern(char *cmd, t_vars *vars)// char *path
{
	pid_t	pid;
	char	*path;

	path = check_cur_dir(vars, cmd);
	if (!path)
		path = check_in_path(vars, cmd);
	pid = fork();
	//signal(SIGINT, );
	if (pid == -1)
		exit_failure("Fork error");
	if (pid == 0)
	{
		//if (execve(path, vars->args, vars->env) < 0)
		//	exit_failure("execve");
		(execve(path, vars->args, vars->env) >= 0) || exit_failure("execve");
		exit(0);
	}
	else
	{
		wait_loop(pid);
		free(path);
	}
	return (0);
	//return (EXIT_SUCCESS);
}

void	choose_cmd(char *cmd, t_vars *vars)
{
	if (cmd == NULL)//if empty command
		return ;
	ft_strcmp(cmd, "echo") || builtin_echo(vars);//builtins execute twice
	ft_strcmp(cmd, "cd") || builtin_cd(vars);
	ft_strcmp(cmd, "pwd") || builtin_pwd(vars);
	ft_strcmp(cmd, "export") || builtin_export(vars);
	ft_strcmp(cmd, "unset") || builtin_unset(vars);
	ft_strcmp(cmd, "env") || builtin_env(vars);
	ft_strcmp(cmd, "exit") || builtin_exit(vars);
	exec_extern(cmd, vars);
	/*
	if (!ft_strcmp(cmd, "echo"))
		return (builtin_echo(vars));
	if (!ft_strcmp(cmd, "cd"))
		return (builtin_cd(vars));
	if (!ft_strcmp(cmd, "pwd"))
		return (builtin_pwd(vars));
	if (!ft_strcmp(cmd, "export"))
		return (builtin_export(vars));
	if (!ft_strcmp(cmd, "unset"))
		return (builtin_unset(vars));
	if (!ft_strcmp(cmd, "env"))
		return (builtin_env(vars));
	if (!ft_strcmp(cmd, "exit"))
		return (builtin_exit(vars));
	return (exec_extern(cmd, vars));
	*/
}


int	execute(t_vars *vars)
{
	int		i;

	vars->flag_pipe = 0;
	vars->flag_redirect = 0;
	i = 0;
//	while (vars->args[i])//no need couse no ; ? but pipes kinda need this
//	{
		if (vars->flag_pipe)
			exec_piped(vars->args[i], vars);
		choose_cmd(vars->args[i], vars);
//		i++;
//	}
	printf("exit status: %d\n", g_exit_status);
	return (0);
}
