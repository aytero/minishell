/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:52:02 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/13 18:51:17 by lpeggy           ###   ########.fr       */
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

	sorted = env_to_char(vars->env);
	size = env_arr_size(sorted);//
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

int	builtin_export(char **cmd, t_vars *vars)
{
	// cut quotes or maybe in parser
	//int		size;
	int		i;

	g_exit_status = 0;
	if (!cmd[1])
	{
		sort_env(vars);
		return (0);
	}
	i = 0;
	while (cmd[++i])
	{
		if (!check_export_arg(cmd[i]))
			continue ;
			//g_exit_status = 1;
		set_env_var(&vars->env, cmd[i]);
		/*
		if (env_exists(vars, cmd[j]))
			continue ;
		size = env_arr_size(vars->env);
		vars->env = realloc_env(vars->env, size + 1);
		vars->env[size] = ft_strdup(cmd[j]);
		*/
	}
	return (0);
}
