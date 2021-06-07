/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:42:12 by lpeggy            #+#    #+#             */
/*   Updated: 2021/04/15 19:49:59 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	return_val(int reader)
{
	if (reader == 0)
		return (0);
	return (1);
}

static char	*sf_add_line(char *reminder)
{
	char	*line;
	size_t	i;
	size_t	len;

	if (!reminder)
		return (0);
	len = 0;
	while (reminder[len] != '\n' && reminder[len] != '\0')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (0);
	i = 0;
	while (reminder[i] != '\n' && reminder[i] != '\0')
	{
		line[i] = reminder[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*sf_update_reminder(char *reminder)
{
	char	*new;
	size_t	i;
	size_t	len;

	if (!reminder)
		return (0);
	len = 0;
	while (reminder[len] != '\n' && reminder[len] != '\0')
		len++;
	if (reminder[len] == '\0')
	{
		free(reminder);
		return (0);
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(reminder) - len + 1));
	if (!new)
		return (0);
	len++;
	i = 0;
	while (reminder[len] != '\0')
		new[i++] = reminder[len++];
	new[i] = '\0';
	free(reminder);
	return (new);
}

static int	sf_read_line(int fd, char **line, char **reminder, t_lst **hd)
{
	char		*buffer;
	int			reader;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	reader = 1;
	while (reader != 0 && !ft_strchr_n(*reminder))
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader == -1)
		{
			free(buffer);
			ft_cleanlst_fd(hd, fd);
			return (-1);
		}
		buffer[reader] = '\0';
		*reminder = ft_strjoin(*reminder, buffer);
	}
	*line = sf_add_line(*reminder);
	*reminder = sf_update_reminder(*reminder);
	free(buffer);
	if (reader == 0)
		ft_cleanlst_fd(hd, fd);
	return (return_val(reader));
}

int	get_next_line(int fd, char **line)
{
	static t_lst	*head;
	t_lst			*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (head == NULL)
		head = ft_lstnew_fd(fd);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = ft_lstnew_fd(fd);
		tmp = tmp->next;
	}
	return ((sf_read_line(tmp->fd, line, &tmp->reminder, &head)));
}
