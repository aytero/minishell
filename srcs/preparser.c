/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:25:59 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/14 17:07:44 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*dollarswap(char *str, char *rkey, int *i, int j)
{
	char	*bef;
	char	*aft;

	bef = ft_substr(str, 0, j);
	aft = ft_strdup(str + *i);
	bef = ft_strjoin_free(bef, rkey);
	bef = ft_strjoin_free(bef, aft);
	free(aft);
	free(str);
	return (bef);
}

static int	word_after(char *str, int i, char *divider)
{
	i = skip_symbs(str, i, divider);
	i = skip_symbs(str, i, " \n\f\v\r\t");
	if (!str[i] || (ft_strchr(">|<", str[i]) && !ft_strchr(divider, '|')))
		return (0);
	return (1);
}

static int	skim(char *str)
{
	int		i;

	i = skip_symbs(str, 0, " \n\f\v\r\t");
	if (!str[i])
		return (0);
	if (str[i] == '|')
		return (!write(2,
				"sh: syntax error near unexpected token `|'\n", 43));
	while (str[i])
	{
		i = if_quotes(str, i);
		if (i == -1 || (ft_strchr("|", str[i]) && !word_after(str, i, "|")))
			return (!write(2, "sh: syntax error\n", 17));
		if (ft_strchr("><", str[i]) && (!ft_strncmp(str + i, "<>", 2)
				|| !ft_strncmp(str + i, ">>>", 3)
				|| !ft_strncmp(str + i, "<<<", 3)
				|| !ft_strncmp(str + i, "><", 2)))
			return (!write(2, "sh: syntax error\n", 17));
		if (ft_strchr("><", str[i]) && !word_after(str, i, "><"))
			return (!write(2,
					"sh: syntax error near unexpected token `newline'\n", 49));
		i++;
	}
	return (1);
}

char	**realloc_arr(char **arr, int size)
 {
 	char	**arr_new;
 	int		i;

 	arr_new = malloc(sizeof(char *) * (size + 1));// one extra for \0
  	if (!arr_new)
  		return (NULL);
  	//memset(env_new, 0, sizeof(char *) * (size + 1));
  	i = 0;
  	while (i < size && arr[i])
  	{
 		arr_new[i] = ft_strdup(arr[i]);
 		i++;
 	}
 	arr_new[size] = 0;
 	free_double_char_arr(arr);
 	return (arr_new);
 }

 char	**delete_line(char **arr, int line_index, int size)
 {
 	char	*to_swap;

 	//printf("2\n");
 	while (arr[line_index + 1])
 	{
  		//swap strings so the last one is empty
  		to_swap = ft_strdup(arr[line_index + 1]);
  		free(arr[line_index]);
  		//env[env_index] = NULL;
  		arr[line_index] = to_swap;
  		line_index++;
  	}
  	arr = realloc_arr(arr, size - 1);
  	return (arr);
  }

static void	deal_spec_symbs(void *ptr, t_vars *vars)
{
	int		i;
	t_proc	*proc;

	proc = (t_proc *)ptr;
	i = -1;
	if (proc->cmd)
		proc->cmd = parse_spec_symbs(proc->cmd, vars);
	while (proc->args[++i])
		proc->args[i] = parse_spec_symbs(proc->args[i], vars);
	i = -1;
	while (proc->args[++i])
	{
		//printf(GREY"%s"RESET, proc->args[i]);
		if (proc->args[i] && !proc->args[i][0])
		//if (!proc->args[i])// && !proc->args[i][0])
		{
 			proc->args = delete_line(proc->args, i, proc->arg_nbr);
 			proc->arg_nbr--;
 			i = -1;
		}
	}
}

void	pre_parser(char *str, t_vars *vars)
{
	t_util	util;
	char	**cmd_line;

	if (!str[0])
	{
		vars->parse_err = 1;
		return ;
	}
	ft_memset(&util, 0, sizeof(t_util));
	(skim(str) && (vars->cmd_nbr = count_elems(str, "|")))
		|| ((vars->parse_err = 1) && (g_exit_status = 258));
	if (vars->parse_err)
		return ;
	vars->pipe_nbr = vars->cmd_nbr - 1;
	if (vars->pipe_nbr)
		vars->flag_pipe = 1;
	((cmd_line = split_arr_if(str, vars->cmd_nbr, &util, cut_cmds))
			&& (make_cmd_list(cmd_line, vars, &util))) || (vars->parse_err = 1);
	free_double_char_arr(cmd_line);
	if (vars->parse_err)
		return ;
	ft_lstiter_param(vars->cmd_arr, &deal_spec_symbs, vars);
}
