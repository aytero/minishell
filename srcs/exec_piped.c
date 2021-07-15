/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 18:24:09 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/15 22:51:26 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	free_double_int_array(int **arr, int size)
{
	int		i;

	i = -1;
	if (arr)
	{
		while (++i < size)
		{
			if (arr[i])
				free(arr[i]);
		}
		free(arr);
	}
}

void	close_pipes(t_vars *vars)
{
	int		i;

	i = -1;
	while (++i < vars->pipe_nbr)
	{
		close(vars->pfd[i][0]);
		close(vars->pfd[i][1]);
	}
	free_double_int_array(vars->pfd, vars->pipe_nbr);
}

void	open_pipes(t_vars *vars)
{
	int		i;

	vars->pfd = malloc(sizeof(int *) * vars->pipe_nbr);
	vars->pfd || exit_failure("malloc", 1);
	i = -1;
	while (++i < vars->pipe_nbr)
	{
		vars->pfd[i] = malloc(sizeof(int) * 2);
		vars->pfd[i] || exit_failure("malloc", 1);
	}
	i = -1;
	while (++i < vars->pipe_nbr)
		pipe(vars->pfd[i]);
}

void	deal_pipes(t_vars *vars, int i)
{
	if (i != 0)
		dup2(vars->pfd[i - 1][0], 0) >= 0 || exit_failure("dup2", 1);
	if (i != vars->pipe_nbr)
		dup2(vars->pfd[i][1], 1) >= 0 || exit_failure("dup2", 1);
}
