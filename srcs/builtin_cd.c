/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:36:45 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/16 16:19:20 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	change_pwd_envs(t_vars *vars, char *old_pwd, char *new_pwd)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", old_pwd);
	set_env_var(&vars->env, tmp);
	free(tmp);
	tmp = NULL;
	tmp = ft_strjoin("PWD=", new_pwd);
	set_env_var(&vars->env, tmp);
	free(tmp);
	tmp = NULL;
}

static char	*deal_tilde_path(char *cmd, t_vars *vars)
{
	char	*tmp;

	tmp = get_env_var(vars->env, "HOME");
	tmp = ft_strjoin(tmp, cmd + 1);
	free(cmd);
	return (tmp);
}

int	builtin_cd(char **cmd, t_vars *vars)
{
	char	*dir;
	char	*old_pwd;
	char	*new_pwd;

	g_exit_status = 0;
	if (cmd[1] && cmd[1][0] == '~')
		cmd[1] = deal_tilde_path(cmd[1], vars);
	!cmd[1] && (dir = get_env_var(vars->env, "HOME"));
	cmd[1] && (dir = cmd[1]);
	old_pwd = getcwd(NULL, 0);
	if (chdir(dir) < 0)
	{
		free(old_pwd);
		return (builtin_error("cd", cmd[1], NULL, 0));
	}
	new_pwd = getcwd(NULL, 0);
	change_pwd_envs(vars, old_pwd, new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}
