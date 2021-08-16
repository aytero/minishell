/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:52:02 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/16 17:35:25 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	env_arr_size(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
		;
	return (i);
}

static int	print_sorted(char **sorted)
{
	int		i;

	i = -1;
	while (sorted[++i])
		printf("declare -x %s\n", sorted[i]);
	free_double_char_arr(sorted);
	return (1);
}

static int	sort_env(t_vars *vars, int j)
{
	int		i;
	int		size;
	char	**sorted;
	char	*tmp;

	sorted = env_to_char(vars->env, 1);
	size = env_arr_size(sorted);
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
				free(tmp);
			}
		}
	}
	return (print_sorted(sorted));
}

int	check_env_arg(char *cmd, char **arg, int i)
{
	char	*tmp;
	int		k;

	if (ft_isdigit(arg[i][0]) || arg[i][0] == '=')
	{
		tmp = ft_strjoin_free(arg[i], "'");
		arg[i] = ft_strjoin("`", tmp);
		free(tmp);
		return (!builtin_error(cmd, arg[i], "not a valid identifier", 1));
	}
	k = -1;
	while (arg[i][++k] && arg[i][k] != '=')
	{
		if ((!ft_isalpha(arg[i][k]) && !ft_isdigit(arg[i][k]) && arg[i][k]
			!= '_') || (ft_strchr(arg[i], '=') && !ft_strcmp(cmd, "unset")))
		{
			tmp = ft_strjoin_free(arg[i], "'");
			arg[i] = ft_strjoin("`", tmp);
			free(tmp);
			return (!builtin_error(cmd, arg[i], "not a valid identifier", 1));
		}
	}
	if (!ft_strchr(arg[i], '=') && !ft_strcmp(cmd, "export"))
		return (0);
	return (1);
}

int	builtin_export(char *cmd, char **args, t_vars *vars)
{
	int		i;

	g_exit_status = 0;
	if (!args[1])
		return (!sort_env(vars, -1));
	i = 0;
	while (args[++i])
	{
		if (!check_env_arg(cmd, args, i))
			continue ;
		if (!set_env_var(&vars->env, args[i]))
			return (builtin_error(cmd, args[i], "malloc error", 1));
	}
	return (0);
}
