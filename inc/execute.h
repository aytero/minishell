/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:51:06 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/16 17:35:15 by lpeggy           ###   ########.fr       */
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

# define DEBUG 0
# define DEBUG_PARSER 0
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
	int			arg_nbr;
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
	int			fd_holder[2];
	int			**pfd;
	char		**path_arr;
	t_list		*env;
	t_list		*cmd_arr;
}				t_vars;

extern int		g_exit_status;

void			rl_replace_line(const char *text, int clear_undo);
void			rl_clear_history(void);

/*		signal.c		*/
void			parent_sig_handler(int signal);
void			sig_handler(int signal);

/*		free_mem.c		*/
void			free_proc(void *ptr);
int				free_mem(t_vars *vars);

/*		env_utils.c		*/
char			*get_env_var(t_list *env, char *key);
int				delete_env_var(t_list **env, char *key);
int				set_env_var(t_list **env, char *env_line);
int				new_env_var(t_list **head, char **kv);
int				replace_env_var(t_list *node, char **kv);

/*		builtin_commands.c		*/
int				builtin_error(char *cmd, char *arg, char *error_mes,
					int errtype);
int				builtin_pwd(t_vars *vars);
int				builtin_unset(char *cmd, char **args, t_vars *vars);
int				builtin_exit(char **cmd, t_vars *vars);

/*		builtin_echo.c		*/
int				builtin_echo(char **cmd);

/*		builtin_cd.c		*/
int				builtin_cd(char **cmd, t_vars *vars);

/*		builtin_export.c		*/
int				builtin_export(char *cmd, char **args, t_vars *vars);
int				check_env_arg(char *cmd, char **arg, int i);

/*		builtin_env.c		*/
int				builtin_env(t_proc *proc, t_list **head);
char			**env_to_char(t_list *env, int flag_exp);
t_list			*env_to_list(char **env);

/*		execute.c		*/
void			execute(t_vars *vars);
int				choose_cmd(t_proc *proc, t_vars *vars);
int				store_stdio(t_vars *vars, int io);
int				restore_stdio(t_vars *vars, int io);

/*		exec_extern.c		*/
int				exec_extern(t_proc *proc, t_vars *vars);
void			wait_loop(void *ptr);

/*		exec_builtin.c		*/
int				exec_builtin(t_vars *vars, t_proc *proc, int cmd_id);

/*		exec_piped.c		*/
void			exec_piped(t_vars *vars);
int				close_pipes(t_vars *vars);
int				deal_pipes(t_vars *vars, t_proc *proc);

/*		deal_redir.c		*/
int				deal_redir(t_proc *proc);
int				deal_heredoc(t_proc *proc, int i);

/*		pathfinder.c		*/
char			*pathfinder(t_vars *vars, char *cmd);

/*		minishell.c		*/
char			**get_path_arr(t_vars *vars);

/*		exit_shell.c		*/
int				exit_failure(char *cmd, char *str, int errtype);
int				report_failure(char *cmd, char *str, int errtype);

#endif
