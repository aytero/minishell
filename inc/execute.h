/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:51:06 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/16 21:54:32 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include "../libft/libft.h"

typedef struct s_cmds
{
	char			*cmd;
	char			**args;
//	int				flag_pipe;
//	int				flag_redirect;
	struct t_cmds	*next;
}					t_cmds;

typedef struct s_vars
{
	int			flag_pipe;
	int			flag_redirect;
	char		**env;
	char		*path;
	char		**path_arr;
	char		**args;
	t_cmds		*cmds;
}				t_vars;

int		g_exit_status;

void	builtin_error(char *cmd, char *arg, char *error_mes);
void	free_double_array(char **arr);
void	replace_env(t_vars *vars, int index, char *new_val);
int		find_env_val_index(t_vars *vars, int index);
int		find_env(t_vars *vars, char *key);
char	**realloc_env(char **env, int size);
int		env_arr_size(char **env);
char	**copy_envp(char **envp, t_vars *vars);
void	exit_failure(char *str);
int		builtin_pwd(t_vars *vars);
int		builtin_echo(t_vars *vars);
int		builtin_cd(t_vars *vars);
int		builtin_export(t_vars *vars);
int		builtin_unset(t_vars *vars);
int		builtin_env(t_vars *vars);
int		builtin_exit(t_vars *vars);
int		exec_extern(char *cmd, t_vars *vars);
int		exec_piped(char *cmd, t_vars *vars);
int		choose_cmd(char *cmd, t_vars *vars);
int		execute(t_vars *vars);

#endif
