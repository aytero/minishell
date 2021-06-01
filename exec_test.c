#include <stdio.h>

int		main(int argc, char **argv)
{
	(void)argc;

	printf("proc from exec_test\n");
	printf("argv[1]: %s\n", argv[1]);
	return (0);
}
