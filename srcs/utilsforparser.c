/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsforparser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:46:26 by ssobchak          #+#    #+#             */
/*   Updated: 2021/08/12 21:33:10 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

char	*lowercasing(char *str)
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
		i = if_quotes(str, i);
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
