/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:25:59 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/13 21:26:40 by lpeggy           ###   ########.fr       */
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

static int	if_quotes(char *str, int i)
{
	if (str[i] == '\'')
		i = skip_until(str, i + 1, '\'');
	if (str[i] == '\"')
		i = skip_until(str, i + 1, '\"');
	if (str[i] == '\\')
		i += 2;
	return (i);
}

static int	skip_pipe(char *str, int i)
{
	while ((str[i] == ' ' || str[i] == '|') && str[i])//and other spaces
		i++;
	return (i);
}

int	count_pipes(char *str)
{
	int		i;
	int		pipe_cntr;
	
	pipe_cntr = 0;
	i = -1;
	while (str[++i])
	{
		i = if_quotes(str, i);
		if (str[i] == '|')
			pipe_cntr++;
	}
	return (pipe_cntr);
}

int	count_args(char *str)//make to count elems
{
	int		i;
	int		arg_nbr;
	
	arg_nbr = 0;
	i = 0;
	while (str[i])
	{
		i = if_quotes(str, i);
		if (str[i] == ' ')
		{
			arg_nbr++;
			i = skipspaces(str, i);
			continue ;
		}
		if (str[i + 1] == '\0')
			arg_nbr++;
		i++;
	}
	return (arg_nbr);
}

char	**cut_cmds(char *str, t_vars *vars)
{
	int		i;
	int		start;
	int		num;
	char	**cmd_line;

	cmd_line = ft_calloc(sizeof(char *), (vars->cmd_nbr + 1));// null last
	if (!cmd_line)
		return (NULL);
	num = 0;
	if (vars->cmd_nbr == 1)
	{
		cmd_line[num] = ft_strdup(str);
		return (cmd_line);
	}
	
	start = 0;
	i = 0;
	while (str[i])
	{
		i = if_quotes(str, i);
		if (str[i] == '|')
		{
			cmd_line[num] = ft_substr(str, start, i - start);
			i = skip_pipe(str, i);
			num++;
			start = i;
			continue ;
		}
		if (num == vars->pipe_nbr)//after last pipe
		{
			cmd_line[num] = ft_strdup(str + i);
			break ;
		}
		i++;
	}
	return (cmd_line);
}

int	skim(char *str)
{
	int		i;
	int		elem_cntr;

	i = -1;
	elem_cntr = 0;
	
	!str[0] || elem_cntr++;
	//if (!str[0])
	//	return (0);
	while (str[++i])
	{
		i = if_quotes(str, i);
		if (i == -1)
		{
			write(1, "wrong input\n", 12);
			return (0);
		}
		if (str[i] == ' ')
			elem_cntr++;
	}
	return (1);
}

void	print_list(t_list **head)
{
	t_list	*tmp;
	int		i;
	int		j;

	j = 0;
	tmp = *head;
	while (tmp)
	{
		i = 0;
		while (((char **)(tmp->content))[i])
		{
			printf("list[%d]	>%s<\n", j, ((char **)(tmp->content))[i]);
			i++;
		}
		tmp = tmp->next;
		j++;
	}
}

void	deal_spec_symbs(void *ptr, t_vars *vars)
{
	int		i;
	char	**arr;

	arr = ptr;
	i = -1;
	while (arr[++i])
		arr[i] = parser(arr[i], vars);
}

int	make_cmd_list(char **cmd_line, t_vars *vars)
{
	char	**args;
	int		i;
	int		arg_nbr;

	arg_nbr = 0;
	i = -1;
	while (++i < vars->cmd_nbr)
	{
		arg_nbr = count_args(cmd_line[i]);
		//printf("			arg_nbr %d\n", arg_nbr);


		args = arg_splitter(cmd_line[i], arg_nbr);
		if (!args)
			return (0);
		ft_lstadd_back(&vars->cmd_arr, ft_lstnew((char **)args));
		//free_double_array(args);//so need new arr for every node
	}
	free_double_array(cmd_line);
	return (1);
}

char	**arg_splitter(char *str, int arg_nbr)
{
	t_flags	flag;
	int 	i;
	int 	n;
	int		k;
	char	*tmp = NULL;
	char	**args;

	ft_bzero(&flag, sizeof(t_flags));
	args = ft_calloc(sizeof(char *), arg_nbr + 1);//ret check
	if (!args)
		return (NULL);

	i = -1;
	n = 0;
	k = 0;
	while (str[++i] && k < arg_nbr)
	{
		if (str[i] == '\'')
			flag.q++;
		if (str[i] == '\"')
			flag.dq++;
		//if "\\"
		//printf("spliter #%d str[%d] = %c\n", k + 1, i, str[i]);
		if ((str[i] == ' ' || str[i] == '\t' || str[i + 1] == '\0')
			&& str[i - 1] != '\\' && !(flag.q % 2) && !(flag.dq % 2))
		{
			//printf("n = %d,   i = %d\n", n, i);
			//printf("k = %d   ", k);

			tmp = ft_substr(str, n, i - n + 1);
			//printf("tmp[%d] = >%s<\n", k, tmp);
			args[k] = ft_strtrim(tmp, " ");
			free(tmp);
			tmp = NULL;
			//printf("args[%d] = >%s<\n", k, args[k]);
			k++;
			n = i;
		}
	}
	return (args);
}

void	pre_parser(char *str, t_vars *vars)
{
	char	**cmd_line;

	cmd_line = NULL;

	//if (!str[0])
	//	return ;
	if (!skim(str))
	{
		cmd_line = ft_calloc(sizeof(char *), 1);
		vars->cmd_arr = ft_lstnew((char **)cmd_line);
		//ft_lstadd_front(&vars->cmd_arr, ft_lstnew((char **)cmd_line));
		return ;
	}
	vars->pipe_nbr = count_pipes(str);
	vars->pipe_nbr == 0 || (vars->flag_pipe = 1);
	vars->cmd_nbr = vars->pipe_nbr + 1;
	cmd_line = cut_cmds(str, vars);
	//if (!cmd_line)
	//	return ;
	make_cmd_list(cmd_line, vars);
	//if (!make_cmd_list(cmd_line, vars))
	//	return ;
	//print_list(&vars->cmd_arr);
	//printf("iemm >%s<\n", ((char**)vars->cmd_arr->content)[0]);
	ft_lstiter_param(vars->cmd_arr, &deal_spec_symbs, vars);
	//print_list(&vars->cmd_arr);

}
