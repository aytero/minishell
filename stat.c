#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int	main()
{
	struct stat	buf;
	FILE		*fp;

//	if ((fp = fopen("p1", "rb")) == NULL)
//		exit (1);
	stat("p1", &buf);
	printf("%hu\n", buf.st_mode);
	printf("%ld\n", buf.st_mtime);
//	fclose(fp);
	return (0);
}
