#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

int		main()
{
	int		fd[2];
	pid_t	pid_1;
	pid_t	pid_2;

	char	buf[5] = {0};

	if (pipe(fd) < 0)
		exit(EXIT_FAILURE);
	if ((pid_1 = fork()) < 0)
		exit(EXIT_FAILURE);
	if (pid_1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		//write smth?
		write(fd[1], "hey\n", 4);
		close(fd[1]);
		//if (execve(args[0], args, envp) < 0)
		//	exit(EXIT_FAILURE);
		exit(0);
	}
	else
	{
		if ((pid_2 = fork()) < 0)
			exit(EXIT_FAILURE);
		if (pid_2 == 0)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			read(fd[0], buf, 4);
			close(fd[0]);
			printf("buf: %s", buf);
			//if (execve(args[0], args, envp) < 0)
			//	exit(EXIT_FAILURE);
			exit(0);
		}
		else
		{
			wait(NULL);
			wait(NULL);
		}
	}
	return (0);
}
