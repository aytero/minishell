/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:46:31 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/13 18:50:32 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	builtin_unset(char **cmd, t_vars *vars)
{
	int		i;
	i = 0;
	while (cmd[++i])
	{
		delete_env_var(&vars->env, cmd[i]);
		/*
		else//mb just ignore and continue
			builtin_error("unset", cmd[i], "not a valid identifier");
			*/
	}
	return (0);
}
