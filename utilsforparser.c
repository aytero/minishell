/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsforparser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:46:26 by ssobchak          #+#    #+#             */
/*   Updated: 2021/06/15 21:06:14 by ssobchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	iskey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char *lowercasing(char *str)
{
	char *strl;

	while(*str)
	{
		if(*str > 64 && *str < 91)
			*str += 32;
		str++;
	}
	return(strl);
}

char	*rightkey(char *key, char **env)
{
	char *rkey;
	int n;
	int k;
	
	n = -1;
	k = 0;
	while (env[++n])
	{
		if (strstr(env[n], key))
		{
			while (env[n][k] && env[n][k] != '=')
				k++;
			rkey = ft_substr(env[n], 0, k);
			if (ft_strcmp(key, rkey) == 0)
				break;
		}
	}
	rkey = ft_substr(env[n], k + 1, ft_strlen(env[n]) - k);
	return (rkey);
}

char	*dollarswap(char *str, char *rkey, int *i, int j)
{
	char *bef;
	char *aft;
	
	bef = ft_substr(str, 0, j);
	aft = ft_strdup(str + *i + 1);
	bef = ft_strjoin(bef, rkey);
	bef = ft_strjoin(bef, aft);
	free(aft);
	return (bef);
}
