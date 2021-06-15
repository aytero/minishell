/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:52:02 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/12 23:32:00 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	check_export_arg(char *new_elem)
{
	int		i;

	if (ft_isdigit(new_elem[0]))
	{
		builtin_error("export", new_elem, "not a valid identifier");
		return (1);
	}
	i = -1;
	while (new_elem[++i] && new_elem[i] != '=')
	{
		if (!ft_isalpha(new_elem[i]) && !ft_isdigit(new_elem[i]))
		{
			builtin_error("export", new_elem, "not a valid identifier");
			return (1);
		}
	}
	return (0);
}

int	builtin_export(t_vars *vars)
{
	// must be an alpha and not started with digit;
	// with no args sorts envs and prints them, without _= var
	// str=value; export str - works as well
	int		i;
	char	**env_new;
	int		size;
	int		j;

	j = -1;
	if (!vars->args[1])
	{
		//builtin_env(vars);
		//sort env
		while (vars->env[++j])
			printf("%s\n", vars->env[j]);
		return (0);
	}

	j = 1;
	size = env_arr_size(vars->env);
	if (check_export_arg(vars->args[j]))
	{
		g_exit_status = 1;
		//exit(1);
		return (1);//exit with error
	}

	env_new = malloc(sizeof(char *) * (size + 1));// one extra for \0
	if (!env_new)
		exit(1);
//	memset(arr_new, 0, sizeof(char *) * (size + 1));
	env_new[size] = 0;

	i = 0;
	while (i < size - 2)//kinda realloc mb is not useful
	{
		env_new[i] = ft_strdup(vars->env[i]);
		i++;
	}
	env_new[i] = ft_strdup(vars->args[j]);
	env_new[++i] = ft_strdup(vars->env[size - 2]);
	free_double_array(vars->env);
	vars->env = env_new;
	return (0);
}
