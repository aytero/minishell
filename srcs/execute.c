/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:49:41 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/15 23:32:34 by lpeggy           ###   ########.fr       */
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

	open_pipes(vars);
	i = 0;
	tmp = vars->cmd_arr;
	while (tmp)
	{
		pid = fork();
		pid >= 0 || exit_failure("fork", 1);
		if (pid == 0)
		{
			deal_pipes(vars, i);
			close_pipes(vars);
			choose_cmd((char **)tmp->content, vars);
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

int	exec_extern(char **cmd, t_vars *vars)// char *path
{
	pid_t	pid;
	char	*path;

	path = pathfinder(vars, cmd[0]);
	//path || exit_failure("No such file or directory", 0);

	pid = fork();
	//signal(SIGINT, );
	if (pid == -1)
		//return (report_failure("fork"));//though wouldnt be able to use ||
		exit_failure("Fork error", 1);
	if (pid == 0)
	{
		(execve(path, cmd, env_to_char(vars->env)) >= 0) || exit_failure("execve", 1);
		exit(0);
	}
	else
	{
		wait_loop(pid);
		free(path);
	}
	return (0);
}

int	choose_cmd(char **cmd, t_vars *vars)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (builtin_echo(cmd));
	if (!ft_strcmp(cmd[0], "cd"))
		return (builtin_cd(cmd, vars));
	if (!ft_strcmp(cmd[0], "pwd"))
		return (builtin_pwd(vars));
	if (!ft_strcmp(cmd[0], "export"))
		return (builtin_export(cmd, vars));
	if (!ft_strcmp(cmd[0], "unset"))
		return (builtin_unset(cmd, vars));
	if (!ft_strcmp(cmd[0], "env"))
		return (builtin_env(vars->env));
	if (!ft_strcmp(cmd[0], "exit"))
		return (builtin_exit(cmd, vars));
	return (exec_extern(cmd, vars));
}

int	execute(t_vars *vars)
{
	vars->flag_redirect = 0;

	if (((char **)(vars->cmd_arr->content))[0] == NULL)
		return (0);
	if (vars->flag_pipe)
		exec_piped(vars);
	else
		choose_cmd((char **)(vars->cmd_arr->content), vars);
	printf("exit status: %d\n", g_exit_status);
	return (0);
}
