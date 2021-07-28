/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:25:59 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/24 23:09:12 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	skip_until(char *str, int i, int sym)
{
	while (str[i])
	{
		if (str[i] == sym && str[i - 1] != '\\')
			return (i);
		i++;
	}
	return (-1);
}

int	if_quotes(char *str, int i)
{
	if (str[i] == '\'')
		i = skip_until(str, i + 1, '\'');
	if (str[i] == '\"')
		i = skip_until(str, i + 1, '\"');
	if (str[i] == '\\')
		i += 2;
	return (i);
}

int	cut_args(char **args, char *str, int *i, int k, t_util *util)
{
	if (str[*i] == '\'')
		util->flag_q++;
	if (str[*i] == '\"')
		util->flag_dq++;
	if ((ft_strchr(" \n\f\v\r\t", str[*i]) || str[*i + 1] == '\0')
		&& str[*i - 1] != '\\' && !(util->flag_q % 2) && !(util->flag_dq % 2))
	{
		args[k] = ft_substr(str, util->start, *i - util->start);// + 1 ?
		*i = skip_symbs(str, *i, " \n\t\f\v\r");
		util->start = *i;
		return (*i);
	}
	return (0);
}

// add pipe as separate node pr pipe flag in each node
// in exec
// while (!pipe)
// if rd in -> deal rd in (and rm node)
// if rd put -> deal rd out
// when go from beginning
// if not rd -> exec
// if pipe -> skip and start again from rd
// OR move rd in each proc but deal them before checking for empty cmd
int	cut_cmds(char **cmd_line, char *str, int *i, int k, t_util *util)
{
	*i = if_quotes(str, *i);
	if (str[*i] == '|')
	{
		cmd_line[k] = ft_substr(str, util->start, *i - util->start);
		//printf(RED"line[%d] = |%s|"RESET, k, cmd_line[k]);
		*i = skip_symbs(str, *i, "|");
		util->start = *i;
		return (*i);// " " ?
	}
	/*
	if (ft_strchr("><", str[*i]))
	{
		if (k == 0)
		{
			*i = skip_symbs(str, *i, "> <");
			while (str[*i] && !ft_strchr(">|< \n\f\v\r\t", str[*i]))// | ?
				(*i)++;
			cmd_line[k] = ft_substr(str, util->start, *i - util->start);
			util->start = *i;
			return (1);
		}
		cmd_line[k] = ft_substr(str, util->start, *i - util->start);
		util->start = *i;
		*i = skip_symbs(str, *i, "><");
		return (*i);
	}
	*/
	return (0);
}

char	**split_arr_if(char *str, int elem_nbr, t_util *util, int (*func)())
{
	int 	i;
	int		k;
	char	**arr;

	arr = ft_calloc(sizeof(char *), elem_nbr + 1);//ret check
	if (!arr)
		return (NULL);
	!(k = 0) && (util->nbr = elem_nbr);
	if (elem_nbr == 1)
	{
		arr[k] = ft_strdup(str);
		return (arr);
	}
	i = skip_symbs(str, 0, " \n\t\f\v\r");//looks safe here
	util->start = i;
	while (str[i] && k < elem_nbr)
	{
		if (k == elem_nbr - 1)
		{
			arr[k] = ft_strdup(str + i);
			DEBUG_PARSER && printf(BLU"line[%d] = |%s|"RESET, k, arr[k]);
			break ;
		}
		if (func(arr, str, &i, k, util))
		{
			DEBUG_PARSER && printf(BLU"line[%d] = |%s|"RESET, k, arr[k]);
			//!(util->start = i) || k++;
			k++;
			continue ;
		}
		i++;
	}
	return (arr);
}


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
	while (((t_proc *)ptr)->args[++i])
		((t_proc *)ptr)->args[i] = parser(((t_proc *)ptr)->args[i], vars);
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
	//vars->pipe_nbr = count_elems(str, "|") - 1;

	((cmd_line = split_arr_if(str, vars->cmd_nbr, &util, cut_cmds))
	 && (make_cmd_list(cmd_line, vars, &util))) || (vars->parse_err = 1);
	if (vars->parse_err)
		return ;
	//DEBUG_PARSER && printf(GREY"\tbefore dealing spec symbs"RESET);
	//DEBUG_PARSER && _print_list(&vars->cmd_arr);

	ft_lstiter_param(vars->cmd_arr, &deal_spec_symbs, vars);

	DEBUG_PARSER && printf(GREY"\tafter all parse"RESET);
	DEBUG_PARSER && _print_list(&vars->cmd_arr);
	//printf(RED"type redir %d\n"RESET, ((t_proc *)(vars->cmd_arr)->content)->type_redir);
	//printf(RED"type redir %s\n"RESET, ((t_proc *)(vars->cmd_arr)->content)->args[0]);
}
