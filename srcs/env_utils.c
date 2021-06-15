/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:24:31 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/15 21:29:06 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

void	builtin_error(char *cmd, char *arg, char *error_mes)
{
	g_exit_status = 1;
//	write(1, assh: unset:`, len);
//	write(1, arg, len);
//	write(1, "':", 2);
//	write(1, error_mes, len);
	printf("assh: %s: `%s': %s\n", cmd, arg, error_mes);
}

int	env_arr_size(char **env)
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
		exit(1);//
		//return (NULL);//error
	//memset(env_new, 0, sizeof(char *) * (size + 1));
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

char	**copy_envp(char **envp, t_vars *vars)
{
	char	**env;
	int		i;

	i = env_arr_size(envp);
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return(NULL);
	//memset(env, 0, sizeof(char *) * (i + 1));
	env[i + 1] = 0;
//	env[i] = 0;
	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			vars->path = ft_strdup(envp[i]);
		env[i] = ft_strdup(envp[i]);
	}
	vars->path_arr = ft_split(vars->path, ':');
	return(env);
}
