/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:28:49 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/11 17:38:40 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	*prep_env_ret(DIR *dir, char *tmp, char *cmd, char *env_path)
{
	tmp = ft_strjoin_sep(env_path, cmd, '/');
	closedir(dir);
	return (tmp);
}

static char	*search_in_environ(t_vars *vars, char *cmd, DIR *dir)
{
	struct dirent	*entry;
	char			*tmp;
	int				i;

	tmp = NULL;
	i = -1;
	DEBUG && printf(GREY"getting path from bin:"RESET);
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
				return (prep_env_ret(dir, tmp, cmd, vars->path_arr[i]));
			entry = readdir(dir);
		}
		closedir(dir);
	}
	return (tmp);
}

static char	*get_abs_path(t_vars *vars, char *cmd)
{
	char		*abs;

	abs = get_env_var(vars->env, "HOME");
	abs = ft_strjoin(abs, cmd + 1);
	DEBUG && printf(GREY"getting abs path:"RESET);
	return (abs);
}

static char	*prep_ret(DIR *dir, char *dirname, char *tmp, char *cmd)
{
	closedir(dir);
	free(dirname);
	tmp = ft_strdup(cmd);
	DEBUG && printf(GREY"getting path from current dir:"RESET);
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
	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0
		|| ft_strncmp(cmd, "/bin/", 5) == 0)
	{
		DEBUG && printf(GREY"getting relatable path:"RESET);
		return (ft_strdup(cmd));
	}
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
