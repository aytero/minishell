/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:52:02 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/01 18:00:06 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	print_sorted(char **sorted)
{
	int		i;

	i = -1;
	while (sorted[++i])
		ft_strchr(sorted[i], '=') && printf("declare -x %s\n", sorted[i]);
	free_double_char_arr(sorted);
	return (1);
}

static int	sort_env(t_vars *vars)
{
	int		i;
	int		j;
	int		size;
	char	**sorted;
	char	*tmp;

	sorted = env_to_char(vars->env);
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
			}
		}
	}
	return (print_sorted(sorted));
}

static int	check_export_arg(char *arg)
{
	char	*tmp;
	int		i;

	if (ft_isdigit(arg[0]))
	{
		tmp = ft_strjoin_free(arg, "'");
		arg = ft_strjoin("`", tmp);
		free(tmp);
		return (!builtin_error("export", arg, "not a valid identifier"));
	}
	if (!ft_strchr(arg, '='))
		return (0);
	i = -1;
	while (arg[++i] && arg[i] != '=')
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]) && arg[i] != '_')
		{
			tmp = ft_strjoin_free(arg, "'");
			arg = ft_strjoin("`", tmp);
			free(tmp);
			return (!builtin_error("export", arg, "not a valid identifier"));
		}
	}
	return (1);
}

int	builtin_export(char **cmd, t_vars *vars)
{
	int		i;

	g_exit_status = 0;
	if (!cmd[1])
		return (!sort_env(vars));
	i = 0;
	while (cmd[++i])
	{
		if (!check_export_arg(cmd[i]))
			continue ;
		if (!set_env_var(&vars->env, cmd[i]))
			return (!builtin_error("export", cmd[i], "malloc error"));
	}
	return (0);
}
