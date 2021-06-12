#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char	*ft_strdup(const char *s1);

int		env_arr_size(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
		;
	return (i);
}

void	free_double_array(char **arr)
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


char	**realloc_env(char **env, int size)
{
	char	**env_new;
	int		i;

	env_new = malloc(sizeof(char *) * (size + 1));// one extra for \0
	if (!env_new)
		//return (NULL);
		exit(1);//
	i = 0;
	while (i < size && env[i])
	{
		env_new[i] = ft_strdup(env[i]);
		i++;
	}
	env_new[size] = 0;
	free_double_array(env);
	return (env_new);
}

char	**copy_envp(char **envp)
{
	char	**env;
	int		i;

	i = env_arr_size(envp);
	env = malloc(sizeof(char *) * (i + 1));//not sure about + 1
	if (!env)
		return(NULL);
	//memset(env, 0, sizeof(char *) * i + 1);
	env[i + 1] = 0;
//	env[i] = 0;
	i = -1;
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	return(env);
}
