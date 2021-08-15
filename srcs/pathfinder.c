/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:28:49 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/15 20:26:47 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	*prep_env_ret(DIR *dir, char *cmd, int i, t_vars *vars)
{
	char	*tmp;

	tmp = ft_strjoin_sep(vars->path_arr[i], cmd, '/');
	closedir(dir);
	free_double_char_arr(vars->path_arr);
	return (tmp);
}

static char	*search_in_environ(t_vars *vars, char *cmd, DIR *dir)
{
	struct dirent	*entry;
	int				i;

	i = -1;
	get_path_arr(vars);
	if (!vars->path_arr[0])
		return (NULL);
	while (vars->path_arr[++i])
	{
		dir = opendir(vars->path_arr[i]);
		if (dir == NULL)
			continue ;
		entry = readdir(dir);
		while (entry != NULL)
		{
			if (ft_strcmp(cmd, entry->d_name) == 0)
				return (prep_env_ret(dir, cmd, i, vars));
			entry = readdir(dir);
		}
		closedir(dir);
	}
	free_double_char_arr(vars->path_arr);
	return (NULL);
}

static char	*get_abs_path(t_vars *vars, char *cmd)
{
	char		*abs;

	abs = get_env_var(vars->env, "HOME");
	abs = ft_strjoin(abs, cmd + 1);
	return (abs);
}

static char	*prep_ret(DIR *dir, char *dirname, char *tmp, char *cmd)
{
	closedir(dir);
	free(dirname);
	tmp = ft_strdup(cmd);
	return (tmp);
}

char	*pathfinder(t_vars *vars, char *cmd)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*tmp;
	char			*dirname;

	if (!ft_strncmp(cmd, "~/", 2))
		return (get_abs_path(vars, cmd));
	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "../", 3)
		|| !ft_strncmp(cmd, "/bin/", 5) || cmd[0] == '/')
		return (ft_strdup(cmd));
	dirname = getcwd(NULL, 0);
	tmp = NULL;
	dir = opendir(dirname);
	if (dir == NULL)
		return (search_in_environ(vars, cmd, dir));
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strcmp(cmd, entry->d_name) == 0)
			return (prep_ret(dir, dirname, tmp, cmd));
		entry = readdir(dir);
	}
	closedir(dir);
	free(dirname);
	return (search_in_environ(vars, cmd, dir));
}
