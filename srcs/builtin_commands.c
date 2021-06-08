/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:42:00 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/08 16:42:54 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int		builtin_pwd(char **args, t_list *env)
{
	char	*pwd;

	//error?
	pwd = getcwd(NULL, 0);
	//if (!pwd)
	//	return (EXIT_FAILURE);
	//write(1, cwd, size);
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

int		builtin_echo(char **args, t_list *env)
{
	int		opt_flag;
	int		i = 1;

	opt_flag = 0;
	if (!args[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	if (ft_strcmp(args[1], "-n") == 0)//ft_strcmp
	{
		opt_flag = 1;
		i++;
		//tmp_args = args->next;
	}
	while (args[i])
	{
		//write args & divide with " "
		write(1, args[i], ft_strlen(args[i]));//sizeof(args[i]) - 1);
		//if (args->next != NULL)
		if (args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (!opt_flag)
		write(1, "\n", 1);
	return (0);
}

int		builtin_cd(char **args, t_list *env)
{
	write(1, "cd here\n", 8);
	return (0);
}

int		builtin_export(char **args, t_list *env)
{
	write(1, "export here\n", 12);
	return (0);
}

int		builtin_unset(char **args, t_list *env)
{
	write(1, "unset here\n", 11);
	return (0);
}

int		builtin_env(char **args, t_list *env)
{
	// just prints all envs
	/*
	int		i;

	i = 0;
	while (env[i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
	*/
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		//printf("%s\n", (char *)tmp->content);
		write(1, (char *)tmp->content, ft_strlen((char *)tmp->content));
		//write(1, tmp->key, ft_strlen(tmp->key));
		//write(1, "=", 1);
		//write(1, tmp->value, ft_strlen(tmp->value));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	return (0);
}

int		builtin_exit(char **args, t_list *env)
{
	//exit with an exit status
	//if (global_error) ???
	// exit(EXIT_FAILURE);
	write(1, "bye!\n", 5);
	exit (EXIT_SUCCESS);
}
