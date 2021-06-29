/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 22:20:19 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/29 20:55:09 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	exit_failure(char *str)
{
	printf("%s: %s\n", str, strerror(errno));
	//g_exit_status = 1;
	g_exit_status = errno;
	//if not in fork free mem (?)
	exit(EXIT_FAILURE);
}
