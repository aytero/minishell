/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_empty_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 20:07:17 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/15 20:13:09 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**realloc_arr(char **arr, int size)
{
	char	**arr_new;
	int		i;

	arr_new = malloc(sizeof(char *) * (size + 1));
	if (!arr_new)
		return (NULL);
	i = 0;
	while (i < size && arr[i])
	{
		arr_new[i] = ft_strdup(arr[i]);
		i++;
	}
	arr_new[size] = 0;
	free_double_char_arr(arr);
	return (arr_new);
}

char	**delete_line(char **arr, int line_index, int size)
{
	char	*to_swap;

	while (arr[line_index + 1])
	{
		to_swap = ft_strdup(arr[line_index + 1]);
		free(arr[line_index]);
		arr[line_index] = to_swap;
		line_index++;
	}
	arr = realloc_arr(arr, size - 1);
	return (arr);
}
