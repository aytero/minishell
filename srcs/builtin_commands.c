/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:42:00 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/12 21:11:53 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	builtin_pwd(t_vars *vars)
{
	char	*pwd;

	(void)vars;

	//error?
	pwd = getcwd(NULL, 0);
	//if (!pwd)
	//	return (EXIT_FAILURE);
	//write(1, cwd, size);
	printf("%s\n", pwd);
	free(pwd);
	g_exit_status = 0;
	return (EXIT_SUCCESS);
}

int	builtin_echo(t_vars *vars)
{
	int		opt_flag;
	int		i = 1;

	opt_flag = 0;
	if (!vars->args[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	if (ft_strcmp(vars->args[1], "-n") == 0)
	{
		opt_flag = 1;
		i++;
		//tmp_args = args->next;
	}
	while (vars->args[i])
	{
		write(1, vars->args[i], ft_strlen(vars->args[i]));//sizeof(args[i]) - 1);
		//if (args->next != NULL)
		if (vars->args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (!opt_flag)
		write(1, "\n", 1);
	return (0);
}

int	builtin_cd(t_vars *vars)
{
	(void)vars;
	write(1, "cd here\n", 8);
	return (0);
}

int	builtin_exit(t_vars *vars)
{
	(void)vars;
	//exit with an exit status
	//if (global_error) ???
	// exit(global_error);
	write(1, "bye!\n", 5);
	exit (EXIT_SUCCESS);
}
