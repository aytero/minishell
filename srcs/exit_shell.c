/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 22:20:19 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/01 20:38:21 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"


int	exit_failure(char *cmd, char *str, int errtype)
{
	if (errtype == 1)
	{
		write(2, "sh: ", 4);
		ft_putstr_fd(cmd, 2);
		write(2, ": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 2);
		//printf("%s: %s\n", str, strerror(errno));
		g_exit_status = errno;
	}
	else
	{
		write(2, "sh: ", 4);
		ft_putstr_fd(cmd, 2);
		write(2, ": ", 2);
		ft_putstr_fd(str, 2);
		write(2, "\n", 2);
		//printf("sh: %s: %s\n", cmd, str);
		//printf("%s\n", str);
		g_exit_status = 1;
	}
	//free_mem(vars);
	//if not in fork free mem (?)
	exit(g_exit_status);
}

int	report_failure(char *cmd, char *str, int errtype)
{
	//free_mem
	if (errtype)
	{
		write(2, "sh: ", 4);
		ft_putstr_fd(cmd, 2);
		write(2, ": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 2);
		//printf("sh: %s: %s\n", cmd, str);
		g_exit_status = errno;

	}
	else
	{
		write(2, "sh: ", 4);
		ft_putstr_fd(cmd, 2);
		write(2, ": ", 2);
		ft_putstr_fd(str, 2);
		write(2, "\n", 2);
		//printf("sh: %s: %s\n", cmd, str);
		//printf("%s\n", str);
		g_exit_status = 1;
	}
	//errtype && printf("%s: %s\n", str, strerror(errno));
	//errtype && (g_exit_status = errno);
	//!errtype && printf("sh: %s: %s\n", cmd, str);
	//!errtype && (g_exit_status = 1);
	//return (0);
	return (g_exit_status);
	//return (1);
}
