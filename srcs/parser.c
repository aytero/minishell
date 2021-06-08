/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:16 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/08 22:36:54 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
void	*realloc(void **ptr, size_t sizr)
{
	*ptr = malloc(size);
	return (*ptr);
}
*/

/*
void	arg_to_lowercase()
{
	int		i = 0;

	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}
*/

/*
void	parse(char *line, t_args *args)
{

	//ft_lstadd_front(args, ft_lstnew(line));//t_lst *args & use struct from libft.h
	//return (args);
}
*/

char	**read_input()// t_arg *arg or char **args
{
	int		ret;
	char	*line;
	char	**args;

	if ((ret = get_next_line(0, &line)) > 0)
	{
		args = ft_split(line, ' ');
		//args[last] = NULL;
		//parse(line, args);
		if (line)
			free(line);
		line = NULL;
	}
	if (ret == 0)
	{
		write(1, "\n", 1);
		exit(0);//exits here after pipe ??
		//exit_minishell();
		//exit(EXIT_SUCCESS);
	}
	//while (get_next_line(0, &line ) > 0)//or read from 0 fd
	return(args);
}
