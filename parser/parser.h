/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:48 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/08 21:56:23 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "execute.h"

typedef struct s_flags
{
	int				dq;
	int				q;
	int				pipe;
	int				cmd;
	int				args;
	int				sp;
}					t_flags;

typedef struct s_args
{
	char			**args;
}					t_args;

int		make_cmd_list(char **cmd_line, t_vars *vars);
//void	arg_splitter(t_args *args, char *str, int cmdnum);
char	**arg_splitter(char *str, int arg_nbr);
void	pre_parser(char *str, t_vars *vars);
int		skim(char *str);

int		iskey(char c);
char	*dollarsign(char *str, int *i, char **env);
char	*slash(char *str, int *i);
char	*quotes(char *str, int *i);
char	*doublequotes(char *str, int *i, char **env);
char	*parser(char *str, t_vars *vars);
char	*rightkey(char *key, char **env);
char	*dollarswap(char *str, char *rkey, int *i, int j);
int		checker(char *str);//
int		skipspaces(char *str, int i);

#endif
