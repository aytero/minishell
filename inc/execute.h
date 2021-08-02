/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:51:06 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/02 22:27:40 by lpeggy           ###   ########.fr       */
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
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "colors.h"

# define DEBUG 1
# define DEBUG_PARSER 1
# define FD_IN 0
# define FD_OUT 1
# define REDIR_IN 0
# define REDIR_OUT 1
# define DB_REDIR_IN 2
# define DB_REDIR_OUT 3

typedef struct s_env_var
{
	char		*key;
	char		*value;
}				t_env_var;

typedef struct s_proc
{
	int			pid;
	int			flag_pipe;
	int			flag_redir;
	int			rd_i;
	int			fd[2];
	int			rd_in_nbr;
	int			rd_out_nbr;
	int			id;
	int			*rd_in_type;
	int			*rd_out_type;
	char		**infiles;
	char		**outfiles;
	char		*cmd;
	char		**args;
}				t_proc;

typedef struct s_vars
{
	int			flag_pipe;
	int			parse_err;
	int			cmd_nbr;
	int			pipe_nbr;
	int			fd[2];
	int			fd_holder[2];
	int			**pfd;
	char		**path_arr;
	t_list		*env;
	t_list		*cmd_arr;
}				t_vars;

int				g_exit_status;

void			rl_replace_line(void);
void			rl_clear_history(void);
void			parent_sig_handler(int signal);
void			sig_handler(int signal);
void			free_proc(void *ptr);
int				free_mem(t_vars *vars);

t_list			*env_to_list(char **env);
char			**env_to_char(t_list *env);
char			*get_env_var(t_list *env, char *key);
int				delete_env_var(t_list **env, char *key);
int				set_env_var(t_list **env, char *env_line);
int				new_env_var(t_list **head, char **kv);
int				replace_env_var(t_list *node, char **kv);
int				check_env_arg(char *cmd, char *arg);

int				builtin_error(char *cmd, char *arg, char *error_mes);
int				builtin_pwd(t_vars *vars);
int				builtin_echo(char **cmd);
int				builtin_cd(char **cmd, t_vars *vars);
int				builtin_export(char *cmd, char **args, t_vars *vars);
int				builtin_unset(char *cmd, char **args, t_vars *vars);
int				builtin_env(t_proc *proc, t_list **head);
int				builtin_exit(char **cmd, t_vars *vars);

int				close_pipes(t_vars *vars);
int				deal_pipes(t_vars *vars, t_proc *proc);
int				deal_redir(t_proc *proc);
void			exec_piped(t_vars *vars);
int				exec_extern(t_proc *proc, t_vars *vars);
int				choose_cmd(t_proc *proc, t_vars *vars);
void			execute(t_vars *vars);
void			wait_loop(void *ptr);
char			*pathfinder(t_vars *vars, char *cmd);
int				exit_failure(char *cmd, char *str, int errtype);
int				report_failure(char *cmd, char *str, int errtype);

#endif
