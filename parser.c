/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:16 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/06 19:14:36 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*realloc(void **ptr, size_t sizr)
{
	//*ptr = malloc(size);
	return (*ptr);
}

void	parse(char *line)
{
	t_args	*args;

	args->cmd = ft_stdup(line);
	//return (args);
}

int	read_input()// t_arg *arg or char **args
{
	int		ret;
	char	*line;

	if ((res = get_next_line(0, &line)) > 0)
	{
		parse(line);
		if (line)
			free(line);
		line = NULL:
	}
	if (ret == 0)
	{
		write(1, "\n", 1);
		exit(0);
		//exit_minishell();
		//exit(EXIT_SUCCESS);
	}
	//while (get_next_line(0, &line ) > 0)//or read from 0 fd
}
