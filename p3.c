#include <stdio.h>
#include <unistd.h>

int		main(int argc, char **argv)
{
	int		i;
	int		ret = 0;
	char	buf[1024] = {0};

	(void)argc;
	printf("prog - %s\n", argv[0]);
	//printf("read from pipe:\n");
	ret = read(0, buf, 1024);
	//printf("%s\n", buf);
	i = 1;
	printf("main args:\n");
	while (argv[i])
	{
		printf("%s\n", argv[i]);
		i++;
	}
	return (0);
}
