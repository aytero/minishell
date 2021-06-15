#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char	*ft_strdup(const char *s1);
int		env_arr_size(char **env);
void	free_double_array(char **arr);
char	**copy_envp(char **envp);
char	**realloc_env(char **env, int size);

int		g_ex_status = 0;

void	builtin_error(char *cmd, char *arg, char *error_mes)
{
	g_ex_status = 1;
//	write(1, assh: unset:`, len);
//	write(1, arg, len);
//	write(1, "':", 2);
//	write(1, error_mes, len);
	printf("assh: %s: `%s': %s\n", cmd, arg, error_mes);
}

char	**builtin_export(char **env, int size, char *new_elem)
{
	// must be an alpha and not started with digit;
	// with no args sorts envs and prints them, without _= var
	// str=value; export str - works as well
	int		i;
	char	**env_new;

	if (isdigit(new_elem[0]))//ft_isdigit
	{
		builtin_error("export", new_elem, "not a valid identifier");
		return (env);
	}
	i = -1;
	while (new_elem[++i] && new_elem[i] != '=')
	{
		if (!isalpha(new_elem[i]))//ft_isalpha
		{
			builtin_error("export", new_elem, "not a valid identifier");
			return (env);
		}
	}
	env_new = malloc(sizeof(char *) * (size + 1));// one extra for \0
	if (!env_new)
		exit(1);
//	memset(arr_new, 0, sizeof(char *) * (size + 1));
	env_new[size] = 0;

	i = 0;
	while (i < size - 2)
	{
		env_new[i] = ft_strdup(env[i]);
		i++;
	}

	env_new[i] = ft_strdup(new_elem);
	env_new[++i] = ft_strdup(env[size - 2]);

	free_double_array(env);
	return (env_new);
}


int		find_env(char **env, char *key)
{
	int		i;

	i = 0;
	while (env[i])
	{
		//if (ft_strnstr(env[i]), key)
		if (strncmp(env[i], key, strlen(key)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**delete_env(char **env, int env_index)
{
	int		size;
	char	*to_swap;

	size = env_arr_size(env);
	while (env[env_index + 1])
	{
		//swap strings so the last one is empty
		to_swap = ft_strdup(env[env_index + 1]);
		free(env[env_index]);
		//env[env_index] = NULL;
		env[env_index] = to_swap;
		env_index++;
	}
	env = realloc_env(env, env_arr_size(env) - 1);
	return (env);
}

char	**builtin_unset(char **env, char *key)
{
	int		env_index;//maybe use size_t & ssize_t
	int		i;
//	t_args	tmp;

	// args may be written ony by one
//	tmp = tmp->next// 0 arg is prog name/ will be lists thou
//	while (tmp)
//	{
//		main loop
//		tmp = tmp->next
//	}
	env_index = -1;
	i = -1;
	if (!strchr(key, '='))//ft_strchr
		return (env);
	while (env[++i])
	{
		env_index = find_env(env, key);
		if (env_index > -1)// manage zero index
		{
			env = delete_env(env, env_index);
			//remove/realloc/all that
			return (env);
		}
		else
		{
			builtin_error("unset", key, "not a valid identifier");
			return (env);
		}
	}
	return (env);
}

int		builtin_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])//AYOO=hehe and AYOO= should be visible but AYOO shouldn't
	{
		if (strchr(env[i], '='))
		{
			//write(1, env[i], ft_strlen(env[i]));//sizeof(env[i]) - 1);
			//write(1, "\n", 1);
			printf("%s\n", env[i]);
		}
		i++;
	}
	return (1);
}

int		main(int argc, char **argv, char **envp)
{
	//printf("str""more");//important
	int		i = 0;
	char	**env;

	int		flag_export = 1;
	int		flag_unset = 1;
	char	*new_elem = "BEB=blushes!";
	char	*new_elem1 = "AYOO=hehe";
	char	*new_elem2 = "PUTNULL=attheend";

	env = copy_envp(envp);

	if (flag_export)
	{
		env = builtin_export(env, env_arr_size(env) + 1, new_elem);
		env = builtin_export(env, env_arr_size(env) + 1, new_elem1);
		env = builtin_export(env, env_arr_size(env) + 1, new_elem2);
		//printf("%d\n", env_arr_size(env));
	}
	//builtin_env(env);

	if (flag_unset)
	{
		env = builtin_unset(env, new_elem2);
		env = builtin_unset(env, "smth");
	}

	//printf("%d\n", env_arr_size(env));
	//builtin_env(env);
	return (0);
}
