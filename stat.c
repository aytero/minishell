#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include "libft/libft.h"

int	execute(char *path, char *cmd, char **envp)
{
	int		pid;
	char	*args[] = {".", "-a", NULL};
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	tmp = ft_strjoin(tmp, cmd);
//	printf("%s\n", tmp);
	pid = fork();
	if (pid == 0)
	{
		if (execve(tmp, args, envp) < 0)
		{
			perror("execve");
			exit(1);
		}
		exit(0);
	}
	else
	{
		wait(NULL);
		free(tmp);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char			*dirname = "minishell";
	FILE			*fp;
	DIR				*dir;
	struct dirent	*entry;
	struct stat		statbuf;
	int				depth = 0;

	char	*pathtmp;
	char	**path;
	int		i = 0;

	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			pathtmp = strdup(envp[i] + 5);
		i++;
	}
	//printf("path %s\n", pathtmp);
	path = ft_split(pathtmp, ':');
	/*
	i = 0;
	while (path[i])
	{
		printf("%s\n", path[i]);
		i++;
	}
*/
	//check if its bin thing and not in . dir
	i = -1;
	while (path[++i])
	{
		if ((dir = opendir(path[i])) == NULL)
		{
			//printf("Error\n");
			//exit(1);
			continue ;
		}
		//chdir(path[i]);
		while ((entry = readdir(dir)) != NULL)
		{
			//lstat(entry->d_name, &statbuf);
		//	if (S_ISDIR(statbuf.st_mode))
		//	{
		//		if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
		//			continue ;
				//printf("dir %s\n", entry->d_name);
		//	}
		//	else
		//	{
				if (strcmp("ls", entry->d_name) == 0)
				{
					printf("%s\n", entry->d_name);
					execute(path[i], entry->d_name, envp);
					closedir(dir);
					return (0);
				}
				//printf("file %s\n", entry->d_name);
	//		}
		}
		//chdir("..");
		closedir(dir);
	}
//	if ((fp = fopen("p1", "rb")) == NULL)
//		exit (1);
//	stat("p1", &statbuf);
//	printf("%hu\n", statbuf.st_mode);
//	printf("%ld\n", statbuf.st_mtime);
//	fclose(fp);
	return (0);
}
