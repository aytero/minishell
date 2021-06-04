/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:49:41 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/03 20:52:56 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//int	execve(const char *pathname, char *const argv[], char *const envp[]);


void	exit_failure(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int		builtin_pwd(char **args)
{
	char	*pwd;

	//error?
	pwd = getcwd(NULL, 0);
	//if (!pwd)
	//	return (EXIT_FAILURE);
	//write(1, cwd, size);
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

int		exec_piped(char **args, char **envp)
{
	//path is args[0]
	int	fd[2];
	pid_t	pid;
	pid_t	pid1;
	int		wpid = 0;//pid_t ?

	char	buf[5] = {0};

	if (pipe(fd) < 0)
		exit_failure("");
	pid = fork();
	if (pid < 0)
		exit_failure("");
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		//check for builtin && exec
		//if (execve(args[0], args, envp) < 0)
			//exit_failure("");
		exit (0);
	}
	else
	{
		//pid1 = fork();
		//if (pid1 < 0)
		//	exit_failure("");
		//if (pid1 == 0)
		//{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			//check for builtin && exec
		//	if (execve(args[0], args, envp) < 0)
			//	exit_failure("");
		//	exit (0);
	//	}
	//	else
	//	{
			//loop waitpid
			wpid = waitpid(pid, &wstatus, WUNTRACED);
		//	wait(NULL);
			wait(NULL);
		}
	}
	return (0);
}

char	*builtins_array[] = {
	"echo", "cd", "pwd", "export", "unset", "env", "exit"
};

int	(*builtins_func[])(char **) = {
	&builtin_echo,
	&builtin_cd,
	&builtin_pwd,
	&builtin_export,
	&builtin_unset,
	&builtin_env,
	&builtin_exit
};

int		exec_extern(char **args, char **envp)// char *path
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	//signal(SIGINT, );
	if (pid == -1)
		exit_failure("");
	else if (pid == 0)
	{
		if (execve(args[0], args, envp) < 0)
			perror("");
		//exit(EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	else
	{
		// while waiting loop
		int		wpid = 0;
		wpid = waitpid(pid, &wstatus, WUNTRACED);
		while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus))
			wpid = waitpid(pid, &wstatus, WUNTRACED);

//		if (waitpid(pid, &wstatus, WUNTRACED | WCONTINUED) == -1)
//			exit_failure("");
	}
	return (EXIT_SUCCESS);
}

int		execute(char **args, char **envp)
{
	int		builtins_number = sizeof(builtins_array) / sizeof(char *);// or 8
	int		i;

	if (args[0] == NULL)//if empty command
		return (1);

	//if builtin
	//else execve
	i = 0;
	while (i < builtins_number)
	{
		if (strcmp(args[0], builtins_array[i]) == 0)// STRCMP => FT_strcmp
			return ((*builtins_func[i])(args));
		i++;
	}
	//return (exec_piped(args, envp));
	return (exec_extern(args, envp));
}





///////////
int		builtin_echo(char **args)
{
	write(1, "echo here\n", 10);
	// check for -n and set flag
	// while args
	// write args & divide with " "
	// if !flag
	//write(1, "\n", 1);
	return (0);
}

int		builtin_cd(char **args)
{
	write(1, "cd here\n", 8);
	return (0);
}

int		builtin_export(char **args)
{
	write(1, "export here\n", 12);
	return (0);
}

int		builtin_unset(char **args)
{
	write(1, "unset here\n", 11);
	return (0);
}

int		builtin_env(char **args)
{
	write(1, "env here\n", 9);
	return (0);
}

int		builtin_exit(char **args)
{
	write(1, "exit here\n", 10);
	return (0);
}
