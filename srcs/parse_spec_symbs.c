/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spec_symbs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:16 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/13 22:43:36 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*dollar_one_letter(char *str, int *i, int j)
{
	char	*key;

	if (str[*i + 1] == '?')
	{
		key = ft_itoa(g_exit_status);
		*i += 2;
		str = dollarswap(str, key, i, j);
		free(key);
		return (str);
	}
	if (ft_isdigit(str[*i + 1]) || ft_strchr(";|", str[*i + 1]))
	{
		*i += 2;
		str = dollarswap(str, NULL, i, j);
		return (str);
	}
	return (str);
}

static char	*dollarsign(char *str, int *i, t_vars *vars)
{
	int		j;
	char	*key;
	char	*rkey;

	j = *i;
	if (ft_strchr("?;|", str[*i + 1]) || ft_isdigit(str[*i + 1]))
		return (dollar_one_letter(str, i, j));
	while (str[++(*i)])
	{
		if (str[*i] != '_' && !ft_isalnum(str[*i]))
			break ;
	}
	if (*i == j + 1)
		return (str);
	key = ft_substr(str, j + 1, *i - j - 1);
	rkey = get_env_var(vars->env, key);
	!rkey && (str = dollarswap(str, NULL, i, j));
	rkey && (str = dollarswap(str, rkey, i, j));
	free(key);
	*i = 0;
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
	(*i)--;
	return (bef);
}

static char	*doublequotes(char *str, int *i)
{
	int		j;
	char	*bef;
	char	*into;
	char	*aft;

	j = *i;
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == '\"')
			break ;
		(*i)++;
	}
	bef = ft_substr(str, 0, j);
	into = ft_substr(str, j + 1, *i - j - 1);
	aft = ft_strdup(str + *i + 1);
	bef = ft_strjoin_free(bef, into);
	bef = ft_strjoin_free(bef, aft);
	free(str);
	free(into);
	free(aft);
	*i = 0;
	return (bef);
}

char	*parse_spec_symbs(char *str, t_vars *vars)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strtrim(str, " \n\f\v\r\t");
	free(str);
	str = tmp;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			str = quotes(str, &i);
			continue ;
		}
		(str[i] == '\"') && (str = doublequotes(str, &i));
		(str[i] == '$' && str[i + 1]) && (str = dollarsign(str, &i, vars));
		i++;
	}
	return (str);
}
