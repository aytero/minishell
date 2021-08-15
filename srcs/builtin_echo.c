/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 22:32:35 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/15 20:12:17 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	echo_check_opt(char *cmd)
{
	int		k;

	k = 1;
	while (cmd[k] == 'n')
		k++;
	if (!cmd[k])
		return (1);
	return (0);
}

int	builtin_echo(char **cmd)
{
	int		opt_flag;
	int		i;

	i = 1;
	opt_flag = 0;
	if (!cmd[1] && write(1, "\n", 1))
		return (0);
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2) && echo_check_opt(cmd[i]))
	{
		opt_flag = 1;
		i++;
	}
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		(cmd[i + 1] != NULL) && write(1, " ", 1);
		i++;
	}
	!opt_flag && write(1, "\n", 1);
	g_exit_status = 0;
	return (0);
}
