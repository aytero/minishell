/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:51:06 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/08 20:42:28 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include "../libft/libft.h"

/*
typedef struct	s_env
{
	char			*key;
	char			*value;
	int				visible;//cause key without val exists but is not visible for print
	struct t_env	*next;
}					t_env;
*/

void	exit_failure(char *str);
int		builtin_pwd(char **args, t_list *env);
int		builtin_echo(char **args, t_list *env);
int		builtin_cd(char **args, t_list *env);
int		builtin_export(char **args, t_list *env);
int		builtin_unset(char **args, t_list *env);
int		builtin_env(char **args, t_list *env);
int		builtin_exit(char **args, t_list *env);
int		exec_extern(char **args, t_list *env);
int		exec_piped(char **args, t_list *env);
int		choose_cmd(char **args, t_list *env);
int		execute(char **args, t_list *env);

#endif
