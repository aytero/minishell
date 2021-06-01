/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:49:41 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/01 22:22:07 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//int	execve(const char *pathname, char *const argv[], char *const envp[]);


static void	exit_failure(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int		builtin_pwd(char **args)
{
	char	*cwd;
	int		size;

	size = 255;
	if (getcwd(cwd, size) == NULL)
		return (EXIT_FAILURE);
	//write(1, cwd, size);
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}

int		builtin_echo(char **args)
{
	write(1, "echo here\n", 10);
}

/*
int		exec_piped(char *path, char **args, char **envp)
{
	//path is awrgs[0]
	int	pfd[2];
	pid_t	pid;
	pid_t	pid1;

	if (pipe(pfd) < 0)
		exit_failure("");
	pid = fork();
	if (pid < 0)
		exit_failure("");
	else if (pid == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		if (execve(args[0], args, envp) < 0)
		exit_failure("");
	}
	else
	{
		pid1 = fork();
		if (pid1 < 0)
			exit_failure("");
		if (pid1 == 0)
		{
			close(pfd[1]);
			dup2(pfd[0], STDIN_FILENO);
			close(pfd[0]);
			if (execve(args[0], args, envp) < 0)
				exit_failure("");
		}
		else
		{
			wait(NULL);
			wait(NULL);
		}
	}
	//return (0);
}
*/

int	(*builtins_func[])(char **) = {
	&builtin_pwd,
	&builtin_echo
}

int		exec_extern(char **args, char **envp)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
		exit_failure("");
	else if (pid == 0)
	{
		if (execve(args[0], args, envp) < 0)
			prerror("");
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
	char	*builtins_array[]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int		builtins_number = 7;// or 8
	int		i;

	if (args[0] == NULL)//if empty command
		return (1);

	//if builtin
	//else execve
	i = 0;
	while (i < builtins_number)
	{
		if (ft_strcmp(args[0], builtins_array[i]) == 0)
			return ((*builtins_func[i](args)));
			//return (1);
		i++;
	}
	return (exec_extern(args, envp));
}
