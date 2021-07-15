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

int	builtin_env(t_list *env)
{
	while (env)
	{
		if (((t_env_var *)env->content)->value != NULL)
		{
			write(1, ((t_env_var *)env->content)->key,
					ft_strlen(((t_env_var *)env->content)->key));
			write(1, "=", 1);
			write(1, ((t_env_var *)env->content)->value,
					ft_strlen(((t_env_var *)env->content)->value));
			write(1, "\n", 1);
		}
		env = env->next;
	}
	g_exit_status = 0;
	return (0);
}
