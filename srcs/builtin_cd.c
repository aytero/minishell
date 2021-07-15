/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:36:45 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/13 21:00:59 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	change_pwd_envs(t_vars *vars, char *old_pwd, char *new_pwd)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", old_pwd);
	set_env_var(&vars->env, old_pwd);
	free(tmp);
	tmp = NULL;
	tmp = ft_strjoin("PWD=", new_pwd);
	set_env_var(&vars->env, new_pwd);
	free(tmp);
	tmp = NULL;
}

int	builtin_cd(char **cmd, t_vars *vars)
{
	char	*dir;
	char	*old_pwd;
	char	*new_pwd;

	g_exit_status = 0;
	if (!cmd[1])
		dir = get_env_var(vars->env, "HOME");// + no free
	else
		dir = cmd[1];
	// if (!dir)
	old_pwd = getcwd(NULL, 0);
	if (chdir(dir) < 0)
	{
		free(old_pwd);
		builtin_error("cd", cmd[1], "No such file or directory");
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	change_pwd_envs(vars, old_pwd, new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}
