/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 22:20:19 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/05 18:05:08 by lpeggy           ###   ########.fr       */
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
	//exit(EXIT_FAILURE);
}
