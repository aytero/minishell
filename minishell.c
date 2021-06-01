#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

static void		sighandler(int signal)
{
	write(1, "sigint recieved\n", 16);
}

int		builtin_pwd()
{
	char	*cwd;
	int		size;

	size = 64;
	if (getcwd(cwd, size) == NULL)
		return (EXIT_FAILURE);
	//write(1, cwd, size);
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}

/*
int		exec_piped()
{
	int	pfd[2];
	pid_t	pid;
	pid_t	pid1;

	if (pipe(pfd) < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		if (execve() < 0)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		pid1 = fork();
		if (pid1 < 0)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
		if (pid1 == 0)
		{
			close();
			dup2();
			close();
			if (execve() < 0)
			{
				perror("");
				exit(EXIT_FAILURE);
			}
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

int		exec_extern()
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, ...) == -1)
			prerror("");
		exit(EXIT_FAILURE);
	}
	else
	{
		// while waiting loop
//		int		wpid = 0;
//		wpid = waitpid(pid, &wstatus, WUNTRACED);
//		while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus))
//			wpid = waitpid(pid, &wstatus, WUNTRACED);

		if (waitpid(pid, &wstatus, WUNTRACED | WCONTINUED) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}
	return (1);
}

int		execute()
{
	if (args[0] == NULL)//if empty command
		return (1);

	//if builtin
	//else execve
	while (i < builtins_number)
	{
		if (ft_strcmp(args[0], builtins_array[i]) == 0)
			return ((*builtin_func[i](args))''
	}
	return (exec_extern(args));
}

int		main(int argc, char **argv, **env)
{
	char	**args;

	if (signal(SIGINT, sighandler) == SIG_ERR)
		exit(EXIT_FAILURE);
	while (1)
	{
		write(1, "assh:> ", 10);
		parse_input();
		execute(args);
		//free(args);
		//free();
	}
	return (0);
	//return (EXIT_SUCCESS);
}
