/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:49:41 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/12 23:59:22 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//int	execve(const char *pathname, char *const argv[], char *const envp[]);


void	exit_failure(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	exec_piped(char *cmd, t_vars *vars)
{
	int	fd[2];
	pid_t	pid;
	pid_t	pid1;
	int		wpid = 0;//pid_t ?
	int		status;

	if (pipe(fd) < 0)
		exit_failure("Pipe error");
	pid = fork();
	if (pid < 0)
		exit_failure("Fork rror");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		//check for builtin && exec
		choose_cmd(cmd, vars);
		//exit_failure("Exec error");
		exit (0);
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
			choose_cmd(vars->args[1], vars);
			exit (0);
			//exit_failure("Exec error");
		}
		else
		{
			//loop waitpid
			//wpid = waitpid(pid, &status, WUNTRACED);
			wait(NULL);
			wait(NULL);
			//close(fd[0]);
			//close(fd[1]);
		}

		//check for builtin && exec
		//choose_cmd(args + 1, env);//kostil
		//printf("args +1 : %s\n", *(args + 1));
		//exit_failure("");
	}
	return (0);
}

char	*find_path(t_vars *vars, char *cmd)
{
//	struct stat	buf;

//	stat("p1", &buf);
//	printf("")

	char	*path;
	//cmd = "ls"
	char	*ptr;
	char	*path_cut;
	int		len;

	path = NULL;
	path_cut = ft_strdup(vars->path);
	len = ft_strlen(path_cut);
	while (path_cut[--len])
	{
		if (path_cut[len] == '/')
		{
			//path = ft_strjoin(path_cut + len, path);//remove free from ft_strjoin to fix this
			path_cut = ft_substr(path_cut, 0, len);//mb add free in ft_substr??
			//printf("CUT %s\n", path_cut);
			//printf("NEW %s\n", path);
		}
	}
	//search in that dir
	//if no – cut next piece
	// use stat/fstat/lstat
	// opendir/readdir
	return (path);
}

int	exec_extern(char *cmd, t_vars *vars)// char *path
{
	pid_t	pid;
	int		wstatus;

	char	*path;
	path = find_path(vars, cmd);
	pid = fork();
	//signal(SIGINT, );
	if (pid == -1)
		exit_failure("Fork error");
	if (pid == 0)
	{
		if (execve(cmd, vars->args, vars->env) < 0)
			exit_failure("");
		exit(0);
	}
	else
	{
		//wait(NULL);
		// while waiting loop
		int		wpid = 0;
		wpid = waitpid(pid, &wstatus, WUNTRACED);
		while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus))
			wpid = waitpid(pid, &wstatus, WUNTRACED);

		/*
		if (WIFEXITED(wstatus))
		{
			int		ex_s;
			ex_s = WEXITSTATUS(wstatus);
			printf("exit status: %d\n", ex_s);
		}
		*/
//		if (waitpid(pid, &wstatus, WUNTRACED | WCONTINUED) == -1)
//			exit_failure("");
	}
	return (0);
	//return (EXIT_SUCCESS);
}

int	choose_cmd(char *cmd, t_vars *vars)
{
	char	*builtins_array[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int		(*builtins_func[])(t_vars *) = {&builtin_echo, &builtin_cd,
			&builtin_pwd, &builtin_export, &builtin_unset, &builtin_env,
			&builtin_exit};
	int		builtins_number;
	int		i;

	if (cmd == NULL)//if empty command
		return (1);
	builtins_number = sizeof(builtins_array) / sizeof(char *);
	i = 0;
	while (i < builtins_number)
	{
		if (ft_strcmp(cmd, builtins_array[i]) == 0)
			return ((*builtins_func[i])(vars));
		i++;
	}
	return (exec_extern(cmd, vars));
}


int	execute(t_vars *vars)
{
	int		pipe_flag = 0;
	int		i;

	i = 0;
//	while (vars->args[i])
//	{
		if (pipe_flag)
			exec_piped(vars->args[i], vars);
		choose_cmd(vars->args[i], vars);
//		i++;
//	}
	return (0);
}
