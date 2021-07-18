/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:16 by lpeggy            #+#    #+#             */
/*   Updated: 2021/07/15 22:04:04 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*dollarsign(char *str, int *i, t_vars *vars)
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
	rkey = get_env_var(vars->env, key);
	str = dollarswap(str, rkey, i, j);
	free(key);
	return (str);
}

char	*slash(char *str, int *i)
{
	char	*bef;
	char	*aft;

	bef = ft_substr(str, 0, *i);
	aft = ft_strdup(str + *i + 1);
	free(str);
	bef = ft_strjoin_free(bef, aft);
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
	bef = ft_strjoin_free(bef, into);
	bef = ft_strjoin_free(bef, aft);
	free(into);
	free(aft);
	free(str);
	return (bef);
}

char	*doublequotes(char *str, int *i, t_vars *vars)
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
			dollarsign(str, i, vars);
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

/*
char	*redir_in(char *str, int *i, t_vars *vars)
{
	char	*filename;
	char	*str_new;
	int		fd;

	(void)vars;
	printf("str %s\n", str);
	printf("str[%d] = |%c|\n", *i, str[*i]);
	(*i)++;
	printf("str[%d] = |%c|\n", *i, str[*i]);
	*i = skipspaces(str, *i);
	filename = ft_strdup(str + *i);
	str_new = ft_substr(str, 0, *i);

	printf("file |%s|\n", filename);
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	(fd >= 0) || exit_failure("open", 1);
	(dup2(fd, 0) >= 1) || exit_failure("dup2", 1);
	close(fd);
	return (str_new);
}
*/

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
			str = doublequotes(str, &i, vars);
		if (str[i] == '$')
			str = dollarsign(str, &i, vars);
	//	if (str[i] == '>')
	//		str = redir_in(str, &i, vars);
	}
	return (str);
}
