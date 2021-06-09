/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:48 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/09 19:22:18 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_args
{
	char			*cmd;
	char			**args;
	struct t_args	*next;
}					t_args;

//void	parse();
char	**read_input();

#endif
