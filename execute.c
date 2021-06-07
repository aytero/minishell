/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:49:41 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/07 23:03:27 by lpeggy           ###   ########.fr       */
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

int		exec_piped(char **args, t_list *env)
{
	int	fd[2];
	pid_t	pid;
	int		wpid = 0;//pid_t ?

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
		choose_cmd(args, env);
		exit_failure("");
		//exit (0); exits somewhere here because pipe flag is always 1 ??
	}
	else
	{
		//loop waitpid
		//wpid = waitpid(pid, &wstatus, WUNTRACED);
		wait(NULL);

		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		//check for builtin && exec
		choose_cmd(args + 1, env);//kostil
		//exit_failure("");
	}
	return (0);
}

int		exec_extern(char **args, t_list *env)// char *path
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	//signal(SIGINT, );
	if (pid == -1)
		exit_failure("");
	else if (pid == 0)
	{
		//execve(args[0], args, env);
		execve(args[0], args, NULL);
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

int		choose_cmd(char **args, t_list *env)
{
	int		builtins_number = sizeof(builtins_array) / sizeof(char *);// or 8
	int		i;

	if (args[0] == NULL)//if empty command
		return (1);

	i = 0;
	while (i < builtins_number)
	{
		if (ft_strcmp(args[0], builtins_array[i]) == 0)
			return ((*builtins_func[i])(args, env));
		i++;
	}
	return (exec_extern(args, env));
}


int		execute(char **args, t_list *env)
{
	int		pipe_flag = 0;

	if (pipe_flag)
		exec_piped(args, env);
	choose_cmd(args, env);
	return (0);
}


///////////

int		builtin_pwd(char **args, t_list *env)
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

int		builtin_echo(char **args, t_list *env)
{
	int		opt_flag;
	int		i = 1;

	opt_flag = 0;
	if (!args[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	if (ft_strcmp(args[1], "-n") == 0)//ft_strcmp
	{
		opt_flag = 1;
		i++;
		//tmp_args = args->next;
	}
	while (args[i])
	{
		//write args & divide with " "
		write(1, args[i], ft_strlen(args[i]));//sizeof(args[i]) - 1);
		//if (args->next != NULL)
		if (args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (!opt_flag)
		write(1, "\n", 1);
	return (0);
}

int		builtin_cd(char **args, t_list *env)
{
	write(1, "cd here\n", 8);
	return (0);
}

int		builtin_export(char **args, t_list *env)
{
	write(1, "export here\n", 12);
	return (0);
}

int		builtin_unset(char **args, t_list *env)
{
	write(1, "unset here\n", 11);
	return (0);
}

int		builtin_env(char **args, t_list *env)
{
	// just prints all envs
	/*
	int		i;

	i = 0;
	while (env[i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
	*/
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		//printf("%s\n", (char *)tmp->content);
		write(1, (char *)tmp->content, ft_strlen((char *)tmp->content));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	return (0);
}

int		builtin_exit(char **args, t_list *env)
{
	//exit with an exit status
	//if (global_error) ???
	// exit(EXIT_FAILURE);
	write(1, "bye!\n", 5);
	exit (EXIT_SUCCESS);
}
