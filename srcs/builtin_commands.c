/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:42:00 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/24 21:25:21 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	builtin_error(char *cmd, char *arg, char *error_mes)
{
	g_exit_status = 1;
//	write(1, assh: unset:`, len);
//	write(1, arg, len);
//	write(1, "':", 2);
//	write(1, error_mes, len);
	printf("sh: %s: `%s': %s\n", cmd, arg, error_mes);
	return (0);
}

int	builtin_unset(char **cmd, t_vars *vars)
{
	int		i;
	i = 0;
	while (cmd[++i])
	{
		delete_env_var(&vars->env, cmd[i]);
		/*
		else//mb just ignore and continue
			builtin_error("unset", cmd[i], "not a valid identifier");
			*/
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
	if (i == 0)//extra check this free later
		free(pwd);
	g_exit_status = 0;
	return (0);
}

int	builtin_echo(char **cmd)
{
	int		opt_flag;
	int		i = 1;

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

	(void)vars;
	//free_memory(vars);
	i = -1;
	if (!cmd[1])
		exit(0);
	while (cmd[1][++i])
	{
		if (!ft_isdigit(cmd[1][i]) && cmd[1][i] != '-')
		{
			builtin_error(cmd[0], cmd[1], "numeric argument required");
			exit(255);
		}
	}
	cmd[2] && builtin_error(cmd[0], cmd[2], "too many arguments");
	if (!cmd[2])
	{
		write(1, "bye!\n", 5);
		if (cmd[1] < 0)
			exit(256 - ft_atoi(cmd[1]));
		else
			exit(ft_atoi(cmd[1]));
	}
	return (0);//
}
