/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:52:02 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/16 22:27:10 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	print_sorted(char **sorted)
{
	int		i;

	i = -1;
	while (sorted[++i])
	{
		if (ft_strchr(sorted[i], '='))
			printf("declare -x %s\n", sorted[i]);
	}
	free_double_array(sorted);	
}

static void	sort_env(t_vars *vars)
{
	int		i;
	int		j;
	int		size;
	char	**sorted;
	char	*tmp;

	size = env_arr_size(vars->env);
	//sorted = NULL;
	sorted = copy_env_arr(vars->env, vars);
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size - 1)
		{
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0)
			{
				tmp = ft_strdup(sorted[j]);
				free(sorted[j]);
				sorted[j] = ft_strdup(sorted[j + 1]);
				free(sorted[j + 1]);
				sorted[j + 1] = ft_strdup(tmp);
			}
		}
	}
	print_sorted(sorted);
}

void	replace_env(t_vars *vars, int index, char *new_val)
{
	char	*new_env;
	int		k;

	new_env = NULL;
	k = find_env_val_index(vars, index);
	new_env = ft_substr(vars->env[index], 0, k + 1);
	new_env = ft_strjoin(new_env, new_val);
	free(vars->env[index]);
	vars->env[index] = new_env;
}

static int	env_exists(t_vars *vars, char *val)
{
	int		i;
	int		j;
	char	*key;

	i = -1;
	if (ft_strchr(val, '='))
	{
		while (val[++i])
		{
			if (val[i] == '=')//manage env without =
				break ;
		}
		key = ft_substr(val, 0, i);
		j = find_env(vars, key);
		if (j > -1)//getkey
		{
			replace_env(vars, j, val + i + 1);
			return (1);
		}
	}
	else
	{
		i = find_env(vars, val);
		if (i > -1)
			return (1);
	}
	return (0);
}

static int	check_export_arg(char *arg)
{
	int		i;

	if (ft_isdigit(arg[0]))
	{
		builtin_error("export", arg, "not a valid identifier");
		return (0);
	}
	i = -1;
	while (arg[++i] && arg[i] != '=')
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]) && arg[i] != '_')
		{
			builtin_error("export", arg, "not a valid identifier");
			return (0);
		}
	}
	return (1);
}

int	builtin_export(t_vars *vars)
{
	// cut quotes or maybe in parser
	int		size;
	int		j;

	g_exit_status = 0;
	if (!vars->args[1])
	{
		sort_env(vars);
		return (0);
	}
	j = 0;
	while (vars->args[++j])
	{
		if (!check_export_arg(vars->args[j]))
			continue ;
			//g_exit_status = 1;
		if (env_exists(vars, vars->args[j]))
			continue ;
		size = env_arr_size(vars->env);
		vars->env = realloc_env(vars->env, size + 1);
		vars->env[size] = ft_strdup(vars->args[j]);
	}
	return (0);
}
