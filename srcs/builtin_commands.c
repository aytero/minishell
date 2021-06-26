/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:42:00 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/26 21:09:43 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	builtin_error(char *cmd, char *arg, char *error_mes)
{
	g_exit_status = 1;
//	write(1, assh: unset:`, len);
//	write(1, arg, len);
//	write(1, "':", 2);
//	write(1, error_mes, len);
	printf("assh: %s: `%s': %s\n", cmd, arg, error_mes);
}

int	builtin_pwd(t_vars *vars)
{
	char	*pwd;

	(void)vars;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		g_exit_status = 1;
	//write(1, pwd, sizeof(pwd) - 1);
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
	}
	while (vars->args[i])
	{
		write(1, vars->args[i], ft_strlen(vars->args[i]));//sizeof(args[i]) - 1);
		if (vars->args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (!opt_flag)
		write(1, "\n", 1);
	g_exit_status = 0;
	return (0);
}

int	builtin_exit(t_vars *vars)
{
	//exit with an exit status
	free_memory(vars);
	write(1, "bye!\n", 5);
	if (g_exit_status != 0)
	{
		//printf("exit status: %d\n", g_exit_status);
		exit(g_exit_status);
	}
	exit(EXIT_SUCCESS);
}
