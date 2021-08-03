/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:42:00 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/03 18:00:06 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	builtin_error(char *cmd, char *arg, char *error_mes)
{
	g_exit_status = 1;
	write(2, "sh: ", 4);
	ft_putstr_fd(cmd, 2);
	write(2, ": ", 2);
	ft_putstr_fd(arg, 2);
	write(2, ": ", 2);
	ft_putstr_fd(error_mes, 2);
	write(2, "\n", 1);
	return (0);
}

int	builtin_unset(char *cmd, char **args, t_vars *vars)
{
	int		i;

	i = 0;
	while (args[++i])
	{
		if (!check_env_arg(cmd, args[i]))
			continue ;
		delete_env_var(&vars->env, args[i]);
	}
	return (0);
}

int	builtin_pwd(t_vars *vars)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = getcwd(NULL, 0);
	!pwd && (i = 1);
	!pwd && (pwd = get_env_var(vars->env, "PWD"));
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	if (i == 0)
		free(pwd);
	g_exit_status = 0;
	return (0);
}

int	builtin_echo(char **cmd)
{
	int		opt_flag;
	int		i;

	i = 1;
	opt_flag = 0;
	if (!cmd[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	!ft_strcmp(cmd[1], "-n") && ((opt_flag = 1) && i++);
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		(cmd[i + 1] != NULL) && write(1, " ", 1);
		i++;
	}
	!opt_flag && write(1, "\n", 1);
	g_exit_status = 0;
	return (0);
}

int	builtin_exit(char **cmd, t_vars *vars)
{
	int		i;

	i = -1;
	if (!cmd[1] && free_mem(vars))
		exit(0);
	while (cmd[1][++i])
	{
		if (!ft_isdigit(cmd[1][i]) && cmd[1][i] != '-')
		{
			builtin_error(cmd[0], cmd[1], "numeric argument required");
			free_mem(vars);
			exit(255);
		}
	}
	cmd[2] && builtin_error(cmd[0], cmd[2], "too many arguments");
	if (!cmd[2] && (cmd[1] < 0 && free_mem(vars)))
		exit(256 - ft_atoi(cmd[1]));
	if (!cmd[2] && free_mem(vars))
		exit(ft_atoi(cmd[1]));
	return (0);
}
