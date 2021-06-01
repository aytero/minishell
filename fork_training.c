#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

static void		sighandler(int signal)
{
	write(1, "sigint recieved\n", 16);
}

int		main()
{
	pid_t	pid;
	int		wstatus;

	if (signal(SIGINT, sighandler) == SIG_ERR)
		exit(1);
		//errExit("signal SIGINT");
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("child proc\n");
		printf("child id %d, child external id %d, parent id %d\n", pid, getpid(), getppid());
		exit(EXIT_SUCCESS);
	}
	else
	{
		//wait(NULL);
		if (waitpid(pid, &wstatus, WUNTRACED | WCONTINUED) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		printf("parent proc\n");
		printf("child id %d, own id %d, parent id %d\n", pid, getpid(), getppid());
		//wait(NULL);
	}
	while (1)
	{
		write(1, "working\n", 8);
		sleep(3);
	}
	//return (0);
	return (EXIT_SUCCESS);
}
