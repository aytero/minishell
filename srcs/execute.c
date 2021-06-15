/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:49:41 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/16 00:01:37 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	exit_failure(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	wait_loop(pid_t pid)
{		
	int		status;
	int		wpid;

	wpid = waitpid(pid, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		wpid = waitpid(pid, &status, WUNTRACED);

	if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
		//printf("exit status: %d\n", g_exit_status);
	}
//	if (waitpid(pid, &status, WUNTRACED | WCONTINUED) == -1)
//		exit_failure("");
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
		exit_failure("Fork error");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		choose_cmd(cmd, vars);
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
		}
		else
		{
			wait_loop(pid);
			wait_loop(pid1);//TODO manage this so loop makes sense
			//wait(NULL);
			//wait(NULL);
			//close(fd[0]);
			//close(fd[1]);
		}
	}
	return (0);
}

int	check_cur_dir(t_vars *vars, char *cmd)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		statbuf;
	char			*tmp;
	char			*dirname;

	//add search in "." and ".."
	dirname = getcwd(NULL, 0);
	tmp = NULL;	
	if ((dir = opendir(dirname)) == NULL)
		return (0);
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_strcmp(cmd, entry->d_name) == 0)
		{
			tmp = ft_strjoin(entry->d_name, "/");
			tmp = ft_strjoin(tmp, cmd);
			closedir(dir);
			free(tmp);
			free(dirname);
			return (0);
		}
	}
	closedir(dir);
	//free(tmp);
	free(dirname);
	return (1);
}

char	*check_in_path(t_vars *vars, char *cmd)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		statbuf;
	char			*tmp;
	char			*tmp2;
	int				i;

	tmp = NULL;
	i = -1;
	while (vars->path_arr[++i])
	{
		if ((dir = opendir(vars->path_arr[i])) == NULL)
			continue ;
		while ((entry = readdir(dir)) != NULL)
		{
			if (ft_strcmp(cmd, entry->d_name) == 0)
			{
				tmp2 = ft_strdup(vars->path_arr[i]);
				tmp = ft_strjoin(tmp2, "/");
				tmp = ft_strjoin(tmp, cmd);
				closedir(dir);
				return (tmp);
			}
		}
		closedir(dir);
	}
	return (tmp);
}

int	exec_extern(char *cmd, t_vars *vars)// char *path
{
	pid_t	pid;

	char	*path;

	if (check_cur_dir(vars, cmd))
		path = check_in_path(vars, cmd);
	pid = fork();
	//signal(SIGINT, );
	if (pid == -1)
		exit_failure("Fork error");
	if (pid == 0)
	{
		if (execve(path, vars->args, vars->env) < 0)
			exit_failure("execve");
		exit (0);
	}
	else
	{
		wait_loop(pid);
		free(path);
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
	int		i;

	vars->flag_pipe = 0;
	vars->flag_redirect = 0;
	i = 0;
//	while (vars->args[i])//no need couse no ; ? but pipes kinda need this
//	{
		if (vars->flag_pipe)
			exec_piped(vars->args[i], vars);
		//check in . dir
		//check if in bins
		choose_cmd(vars->args[i], vars);
//		i++;
//	}
	printf("exit status: %d\n", g_exit_status);
	return (0);
}
