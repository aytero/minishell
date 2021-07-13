/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:51:06 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/08 20:15:24 by lpeggy           ###   ########.fr       */
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
// # include "libft.h"

# include <string.h>

typedef struct s_cmds
{
	char			*cmd;
	char			**args;
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
	int			cmd_nbr;
	int			pipe_nbr;
	t_list		*cmd_arr;
	t_cmds		*cmds;
}				t_vars;

int		g_exit_status;

void	free_memory(t_vars *vars);
void	builtin_error(char *cmd, char *arg, char *error_mes);
void	free_double_array(void *ptr);
void	replace_env(t_vars *vars, int index, char *new_val);
int		find_env_val_index(t_vars *vars, int index);
int		find_env(t_vars *vars, char *key);
char	**realloc_env(char **env, int size);
int		env_arr_size(char **env);
char	**copy_env_arr(char **envp, t_vars *vars);
int		builtin_pwd(t_vars *vars);
int		builtin_echo(t_vars *vars);
int		builtin_cd(t_vars *vars);
int		builtin_export(t_vars *vars);
int		builtin_unset(t_vars *vars);
int		builtin_env(t_vars *vars);
int		builtin_exit(t_vars *vars);
int		exec_extern(char *cmd, t_vars *vars);
int		exec_piped(char *cmd, t_vars *vars);
//char	*check_in_path(t_vars *vars, char *cmd);
//char	*check_cur_dir(t_vars *vars, char *cmd);
char	*pathfinder(t_vars *vars, char *cmd);
int		choose_cmd(char *cmd, t_vars *vars);
int		execute(t_vars *vars);
int		exit_failure(char *str, int errtype);

#endif
