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

typedef struct s_util
{
	int			start;
	int			nbr;
	int			flag_dq;
	int			flag_q;
	int			flag_sp;//
}				t_util;

int				count_elems(char *str, char *divider);
char			**split_arr_if(char *str, int elem_nbr, t_util *util, int (*func)());
int				cut_cmds(char **cmd_line, char *str, int *i, int k, t_util *util);
int				cut_args(char **args, char *str, int *i, int k, t_util *util);
int				make_cmd_list(char **cmd_line, t_vars *vars, t_util *util);
void			pre_parser(char *str, t_vars *vars);
int				skim(char *str);
char			*dollarsign(char *str, int *i, t_vars *vars);
char			*slash(char *str, int *i);
char			*quotes(char *str, int *i);
char			*doublequotes(char *str, int *i, t_vars *vars);
char			*parser(char *str, t_vars *vars);
char			*dollarswap(char *str, char *rkey, int *i, int j);
char			*parse_redir(char *cmd_line, t_proc *proc);
int				if_quotes(char *str, int i);
int				skip_symbs(char *str, int i, char *set);
char			*lowercasing(char *str);

int		checker(char *str);//
int		_print_list(t_list **head);//
int		_print_all_rd(t_proc *proc);

#endif
