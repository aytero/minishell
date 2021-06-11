/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssobchak <ssobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:14:16 by lpeggy            #+#    #+#             */
/*   Updated: 2021/06/11 22:32:55 by ssobchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	*iskey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*dollarsign(char *str, int *i, char *env)
{
	int j;
	int n;
	char *key;
	char *rkey;

	j = *i;
	n = -1;
	while (str[++(*i)])
	{
		if (!iskey(str[*i]))
			break;
	}
	if (*i == j + 1)
		return (str);
	key = ft_substr(str, j + 1, *i - j - 1);
	while (env[++n])
	{
		if (strstr(env[n], key))
		{
			//rkey = ft_ 39:42 vidosek
		}
	}
	free(str);
	free(key);
	return (bef);
}

char	*slash(char *str, int *i)
{
	char *bef;
	char *aft;

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
	int j;
	char *bef;
	char *into;
	char *aft;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			break;
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

char	*doublequotes(char *str, int *i, char *env)
{
	int j;
	char *bef;
	char *into;
	char *aft;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\\' && str[*i + 1] == '\"' || str[*i + 1] == '$'
			|| str[*i + 1] == )
			break;
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

void	parser(char *str, char *env)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			quotes(str, &i);
		if (str[i] == '\\')
			slash(str, &i);
		if (str[i] == '\"')
			doublequotes(str, &i, env);
		if (str[i] == '$')
			dollarsign(str, &i, env);
	}
}

// char	**read_input()// t_arg *arg or char **args
// {
// 	int		ret;
// 	char	*line;
// 	char	**args;

// 	if ((ret = get_next_line(0, &line)) > 0)
// 	{
// 		args = ft_split(line, ' ');
// 		parse(line, args);
// 		if (line)
// 			free(line);
// 		line = NULL;
// 	}
// 	if (ret == 0)
// 	{
// 		write(1, "\n", 1);
// 		exit(0);
// 		exit_minishell();
// 		exit(EXIT_SUCCESS);
// 	}
// 	while (get_next_line(0, &line ) > 0)//or read from 0 fd
// 	return(args);
// }
