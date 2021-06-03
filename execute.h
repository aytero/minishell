/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:51:06 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/03 20:51:38 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>

# include <string.h>

void	exit_failure(char *str);
int		builtin_pwd(char **args);
int		builtin_echo(char **args);
int		builtin_cd(char **args);
int		builtin_export(char **args);
int		builtin_unset(char **args);
int		builtin_env(char **args);
int		builtin_exit(char **args);
int		exec_extern(char **args, char **envp);
int		exec_piped(char **args, char **envp);
int		execute(char **args, char **envp);

#endif
