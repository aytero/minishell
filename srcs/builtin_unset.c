/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:46:31 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/16 22:02:55 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	**delete_env(char **env, int env_index)
{
	char	*to_swap;

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

int	builtin_unset(t_vars *vars)//, char *key)
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
	i = 0;
	while (vars->args[++i])
	{
		//if (!ft_strchr(vars->args[j], '='))// if '=' and it is last symbol
		//	return (1);
		env_index = find_env(vars, vars->args[i]);
		if (env_index > -1)
			vars->env = delete_env(vars->env, env_index);
		else//mb just ignore and continue
			builtin_error("unset", vars->args[i], "not a valid identifier");
	}
	return (0);
}
