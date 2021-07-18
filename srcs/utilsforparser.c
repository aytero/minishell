/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsforparser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:46:26 by ssobchak          #+#    #+#             */
/*   Updated: 2021/07/18 19:43:20 by ssobchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	iskey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

static char *lowercasing(char *str)
{
	while(*str)
	{
		if(*str > 64 && *str < 91)
			*str += 32;
		str++;
	}
	return(str);
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

int	skipspaces(char *str, int i)
{
	while ((str[i] == ' ' || str[i] == '\t') && str[i])
		i++;
	return (i);
}

char *true_lowercasing(char *str)
{
	if (str[0] == 'e' && str[1] == 'n' && str[3] == 'v')
		lowercasing(str);
	if (str[0] == 'p' && str[1] == 'w' && str[3] == 'd')
		lowercasing(str);
	if (str[0] == 'e' && str[1] == 'c' && str[3] == 'h')
		lowercasing(str);
	if (str[0] == 'e' && str[1] == 'x' && str[3] == 'i')
		lowercasing(str);
	return(str);
}