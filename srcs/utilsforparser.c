/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsforparser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:46:26 by ssobchak          #+#    #+#             */
/*   Updated: 2021/08/11 20:56:43 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	_print_all_rd(t_proc *proc)
{
	int		i;

	i = -1;
	while (++i < proc->rd_in_nbr)
	{
		printf(GREY"infile[%d] = |%s|"RESET, i, proc->infiles[i]);
		printf(GREY"infile[%d] type = %d"RESET, i, proc->rd_in_type[i]);
	}
	i = -1;
	while (++i < proc->rd_out_nbr)
	{
		printf(GREY"outfile[%d] = |%s|"RESET, i, proc->outfiles[i]);
		printf(GREY"outfile[%d] type = %d"RESET, i, proc->rd_out_type[i]);
	}
	return (1);
}

int	_print_list(t_list **head)
{
	t_list	*tmp;
	t_proc	*proc;
	int		i;
	int		j;

	j = 0;
	tmp = *head;
	while (tmp)
	{
		proc = (t_proc *)tmp->content;
		printf(GREY"node %d  cmd      >%s<"RESET, j, proc->cmd);
		i = 0;
		while (proc->args[i])
		{
			printf(GREY"node %d  arg[%d]   >%s<"RESET, j, i, proc->args[i]);
			i++;
		}
		printf(GREY"rd_in_nbr %d\trd_out_nbr %d"RESET, proc->rd_in_nbr,
				proc->rd_out_nbr);
		printf(GREY"flag rd %d"RESET, proc->flag_redir);
		_print_all_rd(proc);
		tmp = tmp->next;
		j++;
	}
	return (1);
}

static int	skip_until(char *str, int i, int sym)
{
	while (str[i])
	{
		if (str[i] == sym)
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
	return (i);
}


char *lowercasing(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] > 64 && str[i] < 91)
			str[i] += 32;
	}
	return (str);
}


int	skip_symbs(char *str, int i, char *set)
{
	while (str[i] && ft_strchr(set, str[i]))
			i++;
	return (i);
}

int	count_elems(char *str, char *divider)
{
	int		i;
	int		elems_nbr;
	
	elems_nbr = 0;
	i = 0;
	!ft_strchr("><", str[i]) && (i = skip_symbs(str, 0, divider));
	while (str[i])
	{
		//printf(RED"%s"RESET, str + i);
		i = if_quotes(str, i);
		//printf(RED"%s"RESET, str + i);
		if (ft_strchr(divider, str[i]))
		{
			elems_nbr++;
			i = skip_symbs(str, i, divider);
			continue ;
		}
		(str[i + 1] == '\0') && (elems_nbr++);
		i++;
	}
	return (elems_nbr);
}
