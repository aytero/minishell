/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_int_arr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 16:28:44 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/01 16:32:04 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_double_int_arr(int **arr, int size)
{
	int		i;

	i = -1;
	if (arr)
	{
		while (++i < size)
		{
			if (arr[i])
				free(arr[i]);
		}
		free(arr);
	}
}
