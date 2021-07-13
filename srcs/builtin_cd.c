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
	int		i;

	i = find_env(vars, "OLDPWD");
	if (i > -1)
		replace_env(vars, i, old_pwd);
	i = find_env(vars, "PWD");
	if (i > -1)
		replace_env(vars, i, new_pwd);
	//error?
}

static char	*find_home_dir(t_vars *vars)
{
	int		i;
	char	*dir;

	dir = NULL;
	i = find_env(vars, "HOME");
	if (i > -1)
		dir = ft_strdup(vars->env[i] + 5);
	return (dir);
}

int	builtin_cd(char **cmd, t_vars *vars)
{
	char	*dir;
	char	*old_pwd;
	char	*new_pwd;

	g_exit_status = 0;
	if (!cmd[1])
		dir = find_home_dir(vars);//check for -1
	else
		dir = cmd[1];
	// if (!dir)
	old_pwd = getcwd(NULL, 0);
	if (chdir(dir) < 0)
	{
		free(old_pwd);
		if (!cmd[1])
			free(dir);
		builtin_error("cd", cmd[1], "No such file or directory");
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	change_pwd_envs(vars, old_pwd, new_pwd);
	if (!cmd[1])
		free(dir);
	free(old_pwd);
	free(new_pwd);
	return (0);
}
