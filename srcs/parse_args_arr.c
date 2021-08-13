/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 20:18:00 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/13 22:31:43 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	cut_args(char **args, char *str, int *i, t_util *util)
{
	if (str[*i] == '\'')
		util->flag_q++;
	if (str[*i] == '\"')
		util->flag_dq++;
	if (ft_strchr(" \n\f\v\r\t", str[*i])
		&& !(util->flag_q % 2) && !(util->flag_dq % 2))
	{
		args[util->k] = ft_substr(str, util->start, *i - util->start);
		*i = skip_symbs(str, *i, " \n\t\f\v\r");
		util->start = *i;
		return (*i);
	}
	return (0);
}

int	cut_cmds(char **cmd_line, char *str, int *i, t_util *util)
{
	*i = if_quotes(str, *i);
	if (str[*i] == '|')
	{
		cmd_line[util->k] = ft_substr(str, util->start, *i - util->start);
		*i = skip_symbs(str, *i, "|");
		util->start = *i;
		return (*i);
	}
	return (0);
}

char	**split_arr_if(char *str, int elem_nbr, t_util *util, int (*func)())
{
	int		i;
	char	**arr;

	arr = ft_calloc(sizeof(char *), elem_nbr + 1);
	if (!arr && report_failure("malloc", NULL, 0))
		return (NULL);
	util->nbr = elem_nbr;
	(elem_nbr == 1 && arr[util->k]) && (arr[util->k] = ft_strdup(str));
	if (elem_nbr == 1 && arr[util->k])
		return (arr);
	i = skip_symbs(str, 0, " \n\t\f\v\r");
	util->start = i;
	while (str[i] && util->k < elem_nbr)
	{
		(util->k == elem_nbr - 1) && (arr[util->k] = ft_strdup(str + i));
		if (util->k == elem_nbr - 1)
			break ;
		if (func(arr, str, &i, util))
		{
			util->k++;
			continue ;
		}
		i++;
	}
	return (arr);
}

static int	get_cmd_name(t_proc *proc)
{
	char	*tmp;

	if (!proc->args[0])
		return (1);
	tmp = ft_strtrim(proc->args[0], " \n\f\v\r\t");
	tmp = lowercasing(tmp);
	if (tmp[0] == '$' || !ft_strcmp(tmp, "export") || !ft_strcmp(tmp, "unset")
		|| !ft_strcmp(tmp, "exit"))
	{
		proc->cmd = ft_strtrim(proc->args[0], " \n\f\v\r\t");
		free(tmp);
	}
	else
		proc->cmd = tmp;
	return (1);
}

int	make_cmd_list(char **cmd_line, t_vars *vars, t_util *util)
{
	int		k;
	int		i;
	t_proc	*proc;

	i = -1;
	while (++i < vars->cmd_nbr)
	{
		proc = ft_calloc(sizeof(t_proc), 1);
		if (!proc && report_failure("malloc", NULL, 0))
			return (0);
		cmd_line[i] = parse_redir(cmd_line[i], proc);
		proc->arg_nbr = count_elems(cmd_line[i], " \n\f\v\r\t");
		ft_memset(util, 0, sizeof(t_util));
		proc->args = split_arr_if(cmd_line[i], proc->arg_nbr, util, cut_args);
		if (!proc->args || !get_cmd_name(proc))
			return (0);
		k = -1;
		while (proc->rd_in_nbr && ++k < proc->rd_in_nbr)
		{
			if (proc->rd_in_type[k] == 2 && !deal_heredoc(proc, k))
				return (!report_failure(proc->infiles[k], NULL, 0));
		}
		ft_lstadd_back(&vars->cmd_arr, ft_lstnew((t_proc *)proc));
	}
	return (1);
}
