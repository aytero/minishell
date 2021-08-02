/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 18:32:14 by lpeggy            #+#    #+#             */
/*   Updated: 2021/08/02 23:33:45 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	write_heredoc(t_proc *proc, int i)
{
	char	*str;
	int		fd;

	fd = open(proc->infiles[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		exit(1);
	str = readline("> ");
	while (str != NULL && ft_strcmp(str, proc->infiles[i]))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	free(str);
	close(fd);
}

static int	deal_heredoc(t_proc *proc, int i)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		write_heredoc(proc, i);
		exit(0);
	}
	else
	{
		waitpid(pid, 0, 0);
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		if ((i < proc->rd_in_nbr - 1) && unlink(proc->infiles[i]))
			return (0);
		return (1);
	}
}

static int	deal_infiles(t_proc *proc)
{
	int		i;
	int		fd;

	i = -1;
	while (++i < proc->rd_in_nbr)
	{
		if (proc->rd_in_type[i] == 2 && !deal_heredoc(proc, i))
			return (!report_failure(proc->infiles[i], NULL, 1));
		if (proc->rd_in_type[i] == 2)
			continue ;
		fd = open(proc->infiles[i], O_RDONLY);
		if (fd < 0)
			return (!report_failure(proc->infiles[i], NULL, 1));
		close(fd);
	}
	fd = open(proc->infiles[--i], O_RDONLY);
	if (fd < 0)
		return (!report_failure(proc->infiles[i], NULL, 1));
	proc->fd[FD_IN] = dup(fd);
	close(fd);
	if (proc->fd[FD_IN] < 0)
		return (!report_failure(proc->infiles[i], NULL, 1));
	if (proc->rd_in_type[i] == 2 && unlink(proc->infiles[i]))
		return (!report_failure(proc->infiles[i], NULL, 1));
	return (1);
}

static int	deal_outfiles(t_proc *proc)
{
	int		i;
	int		fd;
	int		flags[2];

	flags[0] = O_WRONLY | O_TRUNC | O_CREAT;
	flags[1] = O_WRONLY | O_APPEND | O_CREAT;
	i = -1;
	while (++i < proc->rd_out_nbr)
	{
		fd = open(proc->outfiles[i], flags[proc->rd_out_type[i] / 3], 0644);
		if (fd < 0)
			return (!report_failure(proc->outfiles[i], NULL, 1));
		if (i == proc->rd_out_nbr - 1)
		{
			proc->fd[FD_OUT] = dup(fd);
			if (proc->fd[FD_OUT] < 0)
				return (!report_failure(proc->outfiles[i], NULL, 1));
		}
		close(fd);
	}
	return (1);
}

int	deal_redir(t_proc *proc)
{
	if (proc->rd_out_nbr && !deal_outfiles(proc))
		return (0);
	if (proc->rd_in_nbr && !deal_infiles(proc))
		return (0);
	return (1);
}
