/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsforparser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:46:26 by ssobchak          #+#    #+#             */
/*   Updated: 2021/07/13 17:27:26 by lpeggy           ###   ########.fr       */
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
	//char *strl;

	//strl = NULL;
	while(*str)
	{
		if(*str > 64 && *str < 91)
			*str += 32;
		str++;
	}
	return(str);
	//return(strl);
}

char	*rightkey(char *key, char **env)
{
	char *rkey;
	int n;
	int k;
	
	n = -1;
	k = 0;
	rkey = NULL;
	while (env[++n])
	{
		if (ft_strnstr(env[n], key, ft_strlen(key)))
		{
			while (env[n][k] && env[n][k] != '=')
				k++;
			rkey = ft_substr(env[n], 0, k);
			if (ft_strcmp(key, rkey) == 0)
			{
				free(rkey);
				break ;
			}
			free(rkey);
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
