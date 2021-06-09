#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char	**recreate(char **arr, int size, char *new_elem)
{
	int		i;
	char	**arr_new;

	printf("%d\n", size);
	arr_new = malloc(sizeof(char *) * size);
	if (!arr_new)
		exit(1);

	i = 0;
	while (i < size - 2)
	{
		arr_new[i] = strdup(arr[i]);
		i++;
	}
	arr_new[size - 2] = strdup(new_elem);
	arr_new[size - 1] = strdup(arr[size - 2]);

	//i = env_arr_len(arr_new);
	//printf("len %d\n", i);
	i = 0;
	while (arr_new[i])
	{
		//printf
		i++;
	}
	printf("len %d\n", i);
	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
	return (arr_new);
}
int		env_arr_len(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
		;
		//printf("%s\n", env[i]);
	return (i);
}

int		main(int argc, char **argv, char **envp)
{
	int		i = 0;
	char	**env;

	//printf("str""more");

	i = env_arr_len(envp);
	printf("%d\n", i);
	env = malloc(sizeof(char *) * i);
	if (!env)
		exit(1);

	i = -1;
	while (envp[++i])
		env[i] = strdup(envp[i]);

	int		flag = 1;
	char	*new_elem = "BEB=blushes!";
	i = 0;
	if (flag)
	{
		i = env_arr_len(env);
		env = recreate(env, env_arr_len(env) + 1, new_elem);
	}
	i = -1;
	while (env[++i])
	{
		//write(1, "f\n", 2);
		//printf("%d\n", i);
		//printf("%s\n", env[i]);
	}
	printf("iii %d\n", env_arr_len(env));
	//printf("%s\n", env[i]);
	return (0);
}
