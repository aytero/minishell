/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:16 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/13 17:27:59 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*dollarsign(char *str, int *i, char **env)
{
	int		j;
	char	*key;
	char	*rkey;

	j = *i;
	while (str[++(*i)])
	{
		if (!iskey(str[*i]))
			break ;
		//else
	}
	if (*i == j + 1)
		return (str);
	key = ft_substr(str, j + 1, *i - j - 1);
	rkey = rightkey(key, env);
	str = dollarswap(str, rkey, i, j);
	free(key);
	free(rkey);
	return (str);
}

char	*slash(char *str, int *i)
{
	char	*bef;
	char	*aft;

	bef = ft_substr(str, 0, *i);
	aft = ft_strdup(str + *i + 1);
	free(str);
	bef = ft_strjoin(bef, aft);
	(*i)++;
	free(aft);
	return (bef);
}

char	*quotes(char *str, int *i)
{
	int		j;
	char	*bef;
	char	*into;
	char	*aft;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			break ;
	}
	bef = ft_substr(str, 0, j);
	into = ft_substr(str, j + 1, *i - j - 1);
	aft = ft_strdup(str + *i + 1);
	bef = ft_strjoin(bef, into);
	bef = ft_strjoin(bef, aft);
	free(into);
	free(aft);
	free(str);
	return (bef);
}

char	*doublequotes(char *str, int *i, char **env)
{
	int		j;
	char	*bef;
	char	*into;
	char	*aft;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] == '$'
				|| str[*i + 1] == '\\'))
			str = slash(str, i);
		if (str[*i] == '$')
			dollarsign(str, i, env);
		if (str[*i] == '\"')
			break ;
	}
	bef = ft_substr(str, 0, j);
	into = ft_substr(str, j + 1, *i - j - 1);
	aft = ft_strdup(str + *i + 1);
	bef = ft_strjoin(bef, into);
	bef = ft_strjoin(bef, aft);
	free(str);
	free(into);
	free(aft);
	return (bef);
}

char	*parser(char *str, t_vars *vars)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			str = quotes(str, &i);
		if (str[i] == '\\')
			str = slash(str, &i);
		if (str[i] == '\"')
			str = doublequotes(str, &i, vars->env);
		if (str[i] == '$')
			str = dollarsign(str, &i, vars->env);
	}
	return (str);//
}
