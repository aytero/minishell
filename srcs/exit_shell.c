/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 22:20:19 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/04 19:19:11 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	exit_failure(char *cmd, char *str, int errtype)
{
	if (errtype == 0)
	{
		write(2, "sh: ", 4);
		ft_putstr_fd(cmd, 2);
		write(2, ": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 2);
		g_exit_status = errno;
	}
	else
	{
		write(2, "sh: ", 4);
		ft_putstr_fd(cmd, 2);
		write(2, ": ", 2);
		ft_putstr_fd(str, 2);
		write(2, "\n", 2);
		g_exit_status = errtype;
	}
	exit(g_exit_status);
}

int	report_failure(char *cmd, char *str, int errtype)
{
	if (errtype == 0)
	{
		write(2, "sh: ", 4);
		ft_putstr_fd(cmd, 2);
		write(2, ": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 2);
		g_exit_status = errno;
	}
	else
	{
		write(2, "sh: ", 4);
		ft_putstr_fd(cmd, 2);
		write(2, ": ", 2);
		ft_putstr_fd(str, 2);
		write(2, "\n", 2);
		g_exit_status = errtype;
	}
	return (g_exit_status);
}
