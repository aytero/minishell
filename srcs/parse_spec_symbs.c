/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:16 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/11 23:41:02 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*dollarswap(char *str, char *rkey, int *i, int j)
{
	char *bef;
	char *aft;

	bef = ft_substr(str, 0, j);
	aft = ft_strdup(str + *i + 1);
	bef = ft_strjoin_free(bef, rkey);
	bef = ft_strjoin_free(bef, aft);
	free(aft);
	free(str);
	//*i = -1;
	//*i = j;
	return (bef);
}

static char	*dollarsign(char *str, int *i, t_vars *vars)
{
	int		j;
	char	*key;
	char	*rkey;

	j = *i;
	*i += 1;
	if (str[*i] == '?')
	{
		//printf("%s\n", str + *i + 1);
		key = ft_itoa(g_exit_status);
		//*i += 1;
		str = dollarswap(str, key, i, j);
		free(key);
		return (str);
	}
	if (ft_isdigit(str[*i]))
	{
		//*i += 1;
		str = dollarswap(str, NULL, i, j);
		return (str);
	}
	//if (!ft_isalnum(str[*i] || str[*i] == ''))
	while (str[++(*i)])
	{
		if (str[*i] != '_' && !ft_isalnum(str[*i]))// && str[*i] == '$')
			break ;
	}
	//if (*i == j + 1)
	if (*i == j)
		return (str);
	key = ft_substr(str, j + 1, *i - j - 1);
	//key = ft_substr(str, j + 1, *i - j);
	rkey = get_env_var(vars->env, key);
	!rkey && (str = dollarswap(str, NULL, i, j));
	rkey && (str = dollarswap(str, rkey, i, j));
	free(key);
	//*i = j;
	*i = -1;
	//printf("str + i |%s|\n", str + *i);
	return (str);
}

static char	*quotes(char *str, int *i)
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
	bef = ft_strjoin_free(bef, into);
	bef = ft_strjoin_free(bef, aft);
	free(into);
	free(aft);
	free(str);
	return (bef);
}

static char	*doublequotes(char *str, int *i, t_vars *vars)
{
	int		j;
	char	*bef;
	char	*into;
	char	*aft;

	j = *i;
	while (str[++(*i)])
	{
		//(str[*i] == '$') && (str = dollarsign(str, i, vars));
		//printf("%c\n", str[*i]);
		if (str[*i] == '$' && str[*i + 1] != '\"')
			str = dollarsign(str, i, vars);
		if (str[*i] == '\"')
			break ;
	}
	bef = ft_substr(str, 0, j);
	into = ft_substr(str, j + 1, *i - j - 1);
	aft = ft_strdup(str + *i + 1);
	bef = ft_strjoin_free(bef, into);
	bef = ft_strjoin_free(bef, aft);
	free(str);
	free(into);
	free(aft);
	return (bef);
}

char	*parse_spec_symbs(char *str, t_vars *vars)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strtrim(str, " \n\f\v\r\t");
	free(str);
	str = tmp;
	while (str[++i])
	{
		//printf("%c\n", str[i]);
		(str[i] == '\'') && (str = quotes(str, &i));
		(str[i] == '\"') && (str = doublequotes(str, &i, vars));
		(str[i] == '$') && (str = dollarsign(str, &i, vars));
	}
	return (str);
}
