/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:28:49 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/05 19:35:15 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	*search_in_environ(t_vars *vars, char *cmd)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*tmp;
	char			*tmp2;
	int				i;

	tmp = NULL;
	i = -1;
	while (vars->path_arr[++i])
	{
		if ((dir = opendir(vars->path_arr[i])) == NULL)
			continue ;
		while ((entry = readdir(dir)) != NULL)
		{
			if (ft_strcmp(cmd, entry->d_name) == 0)
			{
				tmp2 = ft_strdup(vars->path_arr[i]);
				tmp = ft_strjoin(tmp2, "/");
				tmp = ft_strjoin(tmp, cmd);
				closedir(dir);
				return (tmp);
			}
		}
		closedir(dir);
	}
	return (tmp);
}

static char	*get_abs_path(t_vars *vars, char *cmd)
{
	char			*abs;

	abs = ft_strdup(vars->env[find_env(vars, "HOME")] + 5);
	abs = ft_strjoin(abs, cmd + 1);
	return (abs);
}

char	*pathfinder(t_vars *vars, char *cmd)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*tmp;
	char			*dirname;

	if (!ft_strncmp(cmd, "~/", 2))
		return (get_abs_path(vars, cmd));
	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0)// || !ft_strncmp(cmd, "~/", 2))
	{
		tmp = ft_strdup(cmd);
		return (tmp);//check access
	}
	dirname = getcwd(NULL, 0);
	tmp = NULL;	
	if ((dir = opendir(dirname)) == NULL)
		return (search_in_environ(vars, cmd));
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_strcmp(cmd, entry->d_name) == 0)
		{
			//tmp = ft_strjoin(entry->d_name, "/");
			//tmp = ft_strjoin(tmp, cmd);
			closedir(dir);
			//free(tmp);
			free(dirname);
			tmp = ft_strdup(cmd);
			return (tmp);
		}
	}
	closedir(dir);
	//free(tmp);
	free(dirname);
	return (search_in_environ(vars, cmd));
}
