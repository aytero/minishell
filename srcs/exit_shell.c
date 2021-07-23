/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 22:20:19 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/15 23:26:22 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	exit_failure(char *str, int errtype)
{
	if (errtype == 1)
	{
		printf("%s: %s\n", str, strerror(errno));
		g_exit_status = errno;
	}
	else
	{
		printf("%s\n", str);
		g_exit_status = 1;
	}
	//if not in fork free mem (?)
	exit(g_exit_status);
}

int	report_failure(char *str, int errtype)
{
	(void)errtype;
	//free_mem
	printf("%s: %s\n", str, strerror(errno));
	g_exit_status = errno;
	//return (0);
	return (1);
}
