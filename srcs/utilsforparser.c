/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsforparser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:46:26 by ssobchak          #+#    #+#             */
/*   Updated: 2021/07/24 21:31:04 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	_print_list(t_list **head)
{
	t_list	*tmp;
	int		i;
	int		j;

	j = 0;
	tmp = *head;
	while (tmp)
	{
		printf(GREY"node %d  cmd      >%s<"RESET, j, ((t_proc *)(tmp->content))->cmd);
		i = 0;
		//while (((char **)(tmp->content))[i])
		while (((t_proc *)(tmp->content))->args[i])
		{
			//printf("list[%d]	>%s<\n", j, ((char **)(tmp->content))[i]);
			printf(GREY"node %d  arg[%d]   >%s<"RESET, j, i, ((t_proc *)(tmp->content))->args[i]);
			i++;
		}
		printf(GREY"flag rd %d"RESET, ((t_proc *)(tmp->content))->flag_redir);
		printf(GREY"type rd %d"RESET, ((t_proc *)(tmp->content))->type_redir);
		printf(GREY"rd filename |%s|"RESET, ((t_proc *)(tmp->content))->filename);
		tmp = tmp->next;
		j++;
	}
	return (1);
}

int	iskey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char *lowercasing(char *str)//dodelat'
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

char	*dollarswap(char *str, char *rkey, int *i, int j)
{
	char *bef;
	char *aft;
	
	bef = ft_substr(str, 0, j);
	aft = ft_strdup(str + *i + 1);
	bef = ft_strjoin_free(bef, rkey);
	bef = ft_strjoin_free(bef, aft);
	free(aft);
	free(str);
	return (bef);
}

// instead of skipspaces && skip_pipe
// i = skip_symbs(str, i, " \n\t\f\v\r");
// i = skip_symbs(str, i, " |");
int	skip_symbs(char *str, int i, char *set)
{
	while (str[i] && ft_strchr(set, str[i]))
			i++;
	return (i);
}

//ignores quotes
// divider = " \n\t\f\v\r" for args cntr
// divider = "|" for pipe (cmd_nbr) cntr
// divider = "><" for redir  cntr
int	count_elems(char *str, char *divider)
{
	int		i;
	int		elems_nbr;
	
	elems_nbr = 0;
	i = skip_symbs(str, 0, divider);
	//if (str[i] == '|')
	//	return (-1);
	while (str[i])
	{
		i = if_quotes(str, i);
		if (ft_strchr(divider, str[i]))
		{
			elems_nbr++;
			i = skip_symbs(str, i, divider);
			continue ;
		}
		if (str[i + 1] == '\0')
			elems_nbr++;
		i++;
	}
	return (elems_nbr);
}
