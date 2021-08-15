/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:48 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/15 20:13:12 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "execute.h"

# define IO_IN 0
# define IO_OUT 1
# define REDIR_IN 0
# define REDIR_OUT 1
# define DB_REDIR_IN 2
# define DB_REDIR_OUT 3

typedef struct s_util
{
	int		k;
	int		start;
	int		nbr;
	int		flag_dq;
	int		flag_q;
}			t_util;

/*		preparser.c		*/
void		pre_parser(char *str, t_vars *vars);
char		*dollarswap(char *str, char *rkey, int *i, int j);

/*		del_empty_args.c		*/
char	**delete_line(char **arr, int line_index, int size);

/*		parse_args_arr.c	*/
int			cut_cmds(char **cmd_line, char *str, int *i, t_util *util);
int			cut_args(char **args, char *str, int *i, t_util *util);
char		**split_arr_if(char *str, int elem_nbr, t_util *util,
				int (*func)());
int			make_cmd_list(char **cmd_line, t_vars *vars, t_util *util);

/*		parse_redirect.c	*/
char		*parse_redir(char *cmd_line, t_proc *proc);

/*		parse_spec_symbs.c	*/
char		*parse_spec_symbs(char *str, t_vars *vars);

/*		utilsforparser.c	*/
int			count_elems(char *str, char *divider);
int			if_quotes(char *str, int i);
int			skip_symbs(char *str, int i, char *set);
char		*lowercasing(char *str);

int			_print_list(t_list **head);
int			_print_all_rd(t_proc *proc);

#endif
