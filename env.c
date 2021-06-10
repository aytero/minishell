#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int		env_arr_len(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
		;
		//printf("%s\n", env[i]);
	return (i);
}

void	free_env_arr(char **arr)
{
	int		i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
		{
			if (arr[i])
				free(arr[i]);
		}
		free(arr);
	}
}

char	**add_env_var(char **arr, int size, char *new_elem)
{
	int		i;
	char	**arr_new;

	arr_new = malloc(sizeof(char *) * size + 1);// one extra for \0
	memset(arr_new, 0, sizeof(char *) * size + 1);
	if (!arr_new)
		exit(1);

	i = 0;
	while (i < size - 2)
	{
		arr_new[i] = strdup(arr[i]);
		i++;
	}
	printf("fresh %d\n", env_arr_len(arr_new));
	arr_new[size - 2] = strdup(new_elem);
	arr_new[size - 1] = strdup(arr[size - 2]);

	free_env_arr(arr);
	return (arr_new);
}

char	**copy_envp(char **envp)
{
	char	**env;
	int		i;

	i = env_arr_len(envp);
	env = malloc(sizeof(char *) * i + 1);//not sure about + 1
	if (!env)
		return(NULL);
//	memset(env, 0, sizeof(char *) * i + 1);
	i = -1;
	while (envp[++i])
		env[i] = strdup(envp[i]);
	return(env);
}

int		builtin_unset(char **env, char *key)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (find_key)
			//remove/realloc/all that
	}
	return (0);
}

int		builtin_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	//printf("str""more");//important
	int		i = 0;
	char	**env;

	int		flag = 1;
//	char	*new_elem = "BEB=blushes!";
	char	*new_elem1 = "AYOO=hehe";//AYOO= should be visible

	env = copy_envp(envp);

	if (flag)//export
	{
//		env = add_env_var(env, env_arr_len(env) + 1, new_elem);
//		printf("%d\n", env_arr_len(env));
		env = add_env_var(env, env_arr_len(env) + 1, new_elem1);
//		printf("%d\n", env_arr_len(env));
	}

	builtin_env(env);
	return (0);
}
