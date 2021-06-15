/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:48 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/15 22:31:19 by ssobchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_args
{
	char			*cmd;
	struct t_args	*next;
}					t_args;


int	iskey(char c);
char	*dollarsign(char *str, int *i, char **env);
char	*slash(char *str, int *i);
char	*quotes(char *str, int *i);
char	*doublequotes(char *str, int *i, char **env);
void	parser(char *str, char **env);
char	*rightkey(char *key, char **env);
char	*dollarswap(char *str, char *rkey, int *i, int j);
int	checker(char *str);

#endif
