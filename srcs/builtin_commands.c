/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:42:00 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/09 21:18:51 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
void	builtin_error()
{
	g_ex_status = 1;
	//write(1, "", len);
}
*/

int		builtin_pwd(char **args, t_list *env)
{
	char	*pwd;

	//error?
	//g_ex_status = 0;
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
	if (ft_strcmp(args[1], "-n") == 0)
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

/*
void	add_env(t_env *env, char **args)
{
	//kinda lst add back but divide by '=' and use visibility flag
}
*/

int		builtin_export(char **args, t_list *env)
{
	//add_env(env, args);
	//add before back
	return (0);
}

int		builtin_unset(char **args, t_list *env)
{
	write(1, "unset here\n", 11);
	return (0);
}

int		builtin_env(char **args, t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		//printf("%s\n", (char *)tmp->content);
		write(1, (char *)tmp->content, ft_strlen((char *)tmp->content));
		/*
		if (tmp->visible)
		{
			write(1, tmp->key, ft_strlen(tmp->key));
			write(1, "=", 1);
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\n", 1);
		}
		*/
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	//g_ex_status = 0;
	return (0);
}

int		builtin_exit(char **args, t_list *env)
{
	//exit with an exit status
	//if (global_error) ???
	// exit(global_error);
	write(1, "bye!\n", 5);
	exit (EXIT_SUCCESS);
}
