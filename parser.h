/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:48 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/05 23:41:02 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_flags
{
	int				dq;
	int				q;
	int				pipe;
	int				cmd;
	int				args;
	int				space;
}					t_flags;

typedef struct s_args
{
	char			*cmd;
	char			**args;
}					t_args;


void	pre_parser(char *str, char **env);
void	skim(char *str);
int		iskey(char c);
char	*dollarsign(char *str, int *i, char **env);
char	*slash(char *str, int *i);
char	*quotes(char *str, int *i);
char	*doublequotes(char *str, int *i, char **env);
char	**parser(char *str, char **env);
char	*rightkey(char *key, char **env);
char	*dollarswap(char *str, char *rkey, int *i, int j);
int		checker(char *str);
void	cmdsplitter(char *str);
int		skipspaces(char *str, int i);

#endif
