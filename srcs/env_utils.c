/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:24:31 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/16 22:23:12 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

int	find_env_val_index(t_vars *vars, int index)
{
	int		k;
//	char	*val;

	k = 0;
	while (vars->env[index])
	{
		if (vars->env[index][k] == '=')
		{
			//val = ft_substr(vars->env[index][++k]);
			return (k);
		}
		k++;
	}
	return (-1);
}

int	find_env(t_vars *vars, char *key)
{
	int		i;
	char	*full_key;

	//full_key = ft_strjoin(key, "=");//func frees key(commented)
	//or
	full_key = ft_strdup(key);
	full_key = ft_strjoin(full_key, "=");
	i = 0;
	while (vars->env[i])
	{
		if (ft_strncmp(vars->env[i], full_key, ft_strlen(full_key)) == 0)
		{
			free(full_key);
			return (i);
		}
		i++;
	}
	free(full_key);
	return (-1);
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
