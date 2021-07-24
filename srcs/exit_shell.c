/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 22:20:19 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/24 21:46:25 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"


//print errors to fd 2
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

int	report_failure(char *cmd, char *str, int errtype)
{
	//free_mem
	errtype && printf("%s: %s\n", str, strerror(errno));
	errtype && (g_exit_status = errno);
	!errtype && printf("sh: %s: %s\n", cmd, str);
	!errtype && (g_exit_status = 1);
	//return (0);
	return (1);
}
