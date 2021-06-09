/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:49:41 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/09 19:40:32 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//int	execve(const char *pathname, char *const argv[], char *const envp[]);


void	exit_failure(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

// is it global ?
char	*builtins_array[] = {
	"echo", "cd", "pwd", "export", "unset", "env", "exit"
};

int	(*builtins_func[])(char **, t_list *) = {
	&builtin_echo,
	&builtin_cd,
	&builtin_pwd,
	&builtin_export,
	&builtin_unset,
	&builtin_env,
	&builtin_exit
};

int		exec_piped(char *cmd, char **args, t_list *env)
{
	int	fd[2];
	pid_t	pid;
	int		wpid = 0;//pid_t ?
	int		status;

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
		choose_cmd(cmd, args, env);
		exit_failure("");
		//exit (0); exits somewhere here because pipe flag is always 1 ??
	}
	else
	{
		//loop waitpid
		wpid = waitpid(pid, &status, WUNTRACED);
		//wait(NULL);

		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		//check for builtin && exec
		//choose_cmd(args + 1, env);//kostil
		//printf("args +1 : %s\n", *(args + 1));
		//exit_failure("");
	}
	return (0);
}

int		exec_extern(char *cmd, char **args, t_list *env)// char *path
{
	pid_t	pid;
	int		wstatus;

	(void)env;
	pid = fork();
	//signal(SIGINT, );
	if (pid == -1)
		exit_failure("");
	else if (pid == 0)
	{
		//execve(args[0], args, env);//deal later
		execve(cmd, args, NULL);
		exit_failure("");
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

int		choose_cmd(char *cmd, char **args, t_list *env)
{
	int		builtins_number = sizeof(builtins_array) / sizeof(char *);// or 8
	int		i;

	if (args[0] == NULL)//if empty command
		return (1);

	i = 0;
	while (i < builtins_number)
	{
		if (ft_strcmp(cmd, builtins_array[i]) == 0)
			return ((*builtins_func[i])(args, env));
		i++;
	}
	return (exec_extern(cmd, args, env));
}


int		execute(char **args, t_list *env)
{
	int		pipe_flag = 0;
	int		i;

	i = 0;
	while (args[i])
	{
		if (pipe_flag)
			exec_piped(args[i], args, env);
		choose_cmd(args[i], args, env);
		i++;
	}
	return (0);
}
