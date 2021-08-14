/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 19:51:41 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/14 15:48:31 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parser.h"

static void	free_env(void *ptr)
{
	t_env_var	*env_var;

	env_var = (t_env_var *)ptr;
	if (env_var->key)
		free(env_var->key);
	if (env_var->value)
		free(env_var->value);
}

void	free_proc(void *ptr)
{
	t_proc	*proc;

	proc = (t_proc *)ptr;
	if (proc->rd_in_nbr)
	{
		free(proc->rd_in_type);
		free_double_char_arr(proc->infiles);
	}
	if (proc->rd_out_nbr)
	{
		free(proc->rd_out_type);
		free_double_char_arr(proc->outfiles);
	}
	if (proc->cmd)
		free(proc->cmd);
	free_double_char_arr(proc->args);
	if (proc)
		free(proc);
}

int	free_mem(t_vars *vars)
{
	free_double_char_arr(vars->path_arr);
	ft_lstclear(&vars->cmd_arr, free_proc);
	ft_lstclear(&vars->env, free_env);
	return (1);
}
