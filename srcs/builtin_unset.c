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
	int		size;
	char	*to_swap;

	size = env_arr_size(env);
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
	int		j;
//	t_args	tmp;

	// args may be written ony by one
//	tmp = tmp->next// 0 arg is prog name/ will be lists thou
//	while (tmp)
//	{
//		main loop
//		tmp = tmp->next
//	}
	j = 0;
	while (vars->args[++j])
	{
		env_index = -1;
		//if (!ft_strchr(vars->args[j], '='))// if '=' and it is last symbol
		//	return (1);
		i = -1;
		while (vars->env[++i])
		{
			env_index = find_env(vars, vars->args[j]);//args[j] - key
			if (env_index > -1)// manage zero index
			{
				vars->env = delete_env(vars->env, env_index);//remove/realloc/all that
				break ;
			}
			else
			{
				builtin_error("unset", vars->args[j], "not a valid identifier");
				break;
			}
		}
	}
	return (0);
}
