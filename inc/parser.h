/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:48 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/15 21:59:06 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"//
# include <readline/readline.h>
# include <readline/history.h>
# include "execute.h"

# define REDIR_IN 0// <
# define REDIR_OUT 1// >
# define DB_REDIR_IN 2// <<
# define DB_REDIR_OUT 3// >>

typedef struct s_flags
{
	int				dq;
	int				q;
	int				sp;
}					t_flags;

int		make_cmd_list(char **cmd_line, t_vars *vars);
char	**arg_splitter(char *str, int arg_nbr);
void	pre_parser(char *str, t_vars *vars);
int		skim(char *str);
int		iskey(char c);
char	*dollarsign(char *str, int *i, t_vars *vars);
char	*slash(char *str, int *i);
char	*quotes(char *str, int *i);
char	*doublequotes(char *str, int *i, t_vars *vars);
char	*parser(char *str, t_vars *vars);
char	*dollarswap(char *str, char *rkey, int *i, int j);
int		checker(char *str);//
int		skipspaces(char *str, int i);

#endif
