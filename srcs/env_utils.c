/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:24:31 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/13 20:42:29 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

int	find_env_val_index(t_vars *vars, int index)
{
	int		k;

	k = -1;
	while (vars->env[index][++k])
	{
		if (vars->env[index][k] == '=')
			return (k);
	}
	return (-1);
}

int	find_env(t_vars *vars, char *key)
{
	int		i;
	char	*full_key;

	full_key = NULL;
	i = 0;
	while (vars->env[i])
	{
		if (ft_strchr(vars->env[i], '='))
		{
			full_key = ft_strdup(key);
			full_key = ft_strjoin(full_key, "=");
			if (ft_strncmp(vars->env[i], full_key, ft_strlen(full_key)) == 0)
			//if (ft_strncmp(vars->env[i], key, ft_strlen(key)) == 0)
			{
				free(full_key);
				return (i);
			}
		}
		else
		{
			if (ft_strcmp(vars->env[i], key) == 0)
			{
				free(full_key);
				return (i);
			}
		}
		free(full_key);
		i++;
	}
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

char	**realloc_env(char **env, int size)
{
	char	**env_new;
	int		i;

	env_new = malloc(sizeof(char *) * (size + 1));// one extra for \0
	if (!env_new)
		exit_failure("Malloc error", 0);
		//return (NULL);//error
	ft_memset(env_new, 0, sizeof(char *) * (size + 1));
	i = 0;
	while (i < size && env[i])
	{
		env_new[i] = ft_strdup(env[i]);
		i++;
	}
	//env_new[size] = 0;
	free_double_array(env);//
	return (env_new);
}

char	**copy_env_arr(char **envp, t_vars *vars)
{
	char	**env;
	int		i;

	(void)vars;

	i = env_arr_size(envp);
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		exit_failure("Malloc error", 0);
		//return(NULL);
	//memset(env, 0, sizeof(char *) * (i + 1));
//	env[i + 1] = 0;
	env[i] = 0;
	i = -1;
	while (envp[++i])
	{
		//if (ft_strnstr(envp[i], "PATH=", 5))
		//	vars->path = ft_strdup(envp[i]);
		env[i] = ft_strdup(envp[i]);
	}
	//vars->path_arr = ft_split(vars->path, ':');
	return(env);
}
