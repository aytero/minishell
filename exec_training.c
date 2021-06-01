#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		main(int argc, char **argv, char **envp)
{
	char	*args[] = {"./exec_test", "teststr85", NULL};
	int		i = 5;

	(void)argc;
	while (i++ < 10)
		printf("some env: %s\n", envp[i]);
	printf("proc from exec_training before execvp\n");
	execve(args[0], args, envp);
	return (0);
}
