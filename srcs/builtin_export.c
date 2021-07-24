/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:52:02 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/24 21:25:42 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	print_sorted(char **sorted)
{
	int		i;

	i = -1;
	while (sorted[++i])
		ft_strchr(sorted[i], '=') && printf("declare -x %s\n", sorted[i]);
	free_double_array(sorted);	
}

/*
void	print_sorted(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		printf("declare -x %s=%s\n", ((t_env_var *)tmp->content)->key, ((t_env_var *)tmp->content)->value);
		tmp = tmp->next;
	}
}

int	cmp_envs(void *ptr, void *ptr1)//put in .h
{
	int		ret;

	ret = ft_strcmp(((t_env_var *)ptr)->key, ((t_env_var *)ptr1)->key);
	return (ret);
}
*/

static int	sort_env(t_vars *vars)
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
	return (1);

	/*
	t_list	*tmp;

	tmp = vars->env;
	tmp = ft_lstsort(&tmp, cmp_envs);
	print_sorted(&tmp);
	*/
}

static int	check_export_arg(char *arg)
{
	int		i;

	if (!ft_strchr(arg, '='))
		return (0);
	if (ft_isdigit(arg[0]))
		return (builtin_error("export", arg, "not a valid identifier"));
	i = -1;
	while (arg[++i] && arg[i] != '=')
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]) && arg[i] != '_')
			return (builtin_error("export", arg, "not a valid identifier"));
	}
	return (1);
}

int	builtin_export(char **cmd, t_vars *vars)
{
	// cut quotes or maybe in parser
	int		i;

	g_exit_status = 0;
	if (!cmd[1])
		return (!sort_env(vars));
	i = 0;
	while (cmd[++i])
	{
		if (!check_export_arg(cmd[i]))
			continue ;
		set_env_var(&vars->env, cmd[i]);
	}
	return (0);
}
