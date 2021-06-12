/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:45:28 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/12 21:11:04 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	builtin_env(t_vars *vars)
{
	int		i;

	i = 0;
	while (vars->env[i])
	{
		if (ft_strchr(vars->env[i], '='))
		{
			//write(1, env[i], ft_strlen(env[i]));//sizeof(env[i]) - 1);
			//write(1, "\n", 1);
			printf("%s\n", vars->env[i]);
		}
		i++;
	}
	g_exit_status = 0;
	return (0);
}
