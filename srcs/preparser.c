/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:25:59 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/30 21:46:44 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int word_after(char *str, int i, char *divider)
{
	i = skip_symbs(str, i, divider);
	i = skip_symbs(str, i, " \n\f\v\r\t");
	if (!str[i] || ft_strchr(">|<", str[i]))
		return (0);
	return (1);
}

int	skim(char *str)
{
	int		i;

	if (!str[0])
		return (0);
	i = skip_symbs(str, 0, " \n\f\v\r\t");
	if (str[i] == '|')
		return (!write(1, "sh: syntax error\n", 17));
	while (str[i])
	{
		i = if_quotes(str, i);
		if (i == -1 || (ft_strchr("|", str[i]) && !word_after(str, i, "|")))
			return (!write(1, "sh: syntax error\n", 17));
		if (ft_strchr("><", str[i]) && (!word_after(str, i, "><")
			|| !ft_strncmp(str + i, "<>", 2) || !ft_strncmp(str + i, ">>>", 3)
			|| !ft_strncmp(str + i, "<<<", 3) || !ft_strncmp(str + i, "><", 2)))
			return (!write(1, "sh: syntax error\n", 17));
		i++;
	}
	return (1);
}

void	deal_spec_symbs(void *ptr, t_vars *vars)
{
	int		i;

	i = -1;
	//if (((t_proc *)ptr)->cmd)
	//{
		while (((t_proc *)ptr)->args[++i])
			((t_proc *)ptr)->args[i] = parser(((t_proc *)ptr)->args[i], vars);
	//}
}

void	pre_parser(char *str, t_vars *vars)
{
	t_util	util;
	char	**cmd_line;

	ft_memset(&util, 0, sizeof(t_util));
	(skim(str) && (vars->cmd_nbr = count_elems(str, "|")))
		|| (vars->parse_err = 1);
	if (vars->parse_err)
		return ;
	DEBUG_PARSER && printf(GREY"cmd_nbr %d"RESET, vars->cmd_nbr);
	vars->pipe_nbr = vars->cmd_nbr - 1;
	if (vars->pipe_nbr)
		vars->flag_pipe = 1;
	((cmd_line = split_arr_if(str, vars->cmd_nbr, &util, cut_cmds))
	 && (make_cmd_list(cmd_line, vars, &util))) || (vars->parse_err = 1);
	if (vars->parse_err)
		return ;
	//DEBUG_PARSER && printf(GREY"\tbefore dealing spec symbs"RESET);
	//DEBUG_PARSER && _print_list(&vars->cmd_arr);
	ft_lstiter_param(vars->cmd_arr, &deal_spec_symbs, vars);
	DEBUG_PARSER && printf(GREY"\tafter all parse"RESET);
	DEBUG_PARSER && _print_list(&vars->cmd_arr);
}
