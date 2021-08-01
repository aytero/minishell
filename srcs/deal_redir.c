#include "execute.h"

static int	deal_here_doc(t_proc *proc, int i)
{
	int		fd;
	char	*str;

	fd = -1;
	fd = open(proc->infiles[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (0);
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
	if (i < proc->rd_in_nbr - 1)
	{
		if (!unlink(proc->infiles[i]))
			return (0);
	}
	return (1);
}

static int	deal_infiles(t_proc *proc)
{
	int		i;
	int		fd;

	i = -1;
	while (++i < proc->rd_in_nbr)
	{
		if (proc->rd_in_type[i] == 2)
		{
			if (!deal_here_doc(proc, i))
				return (!report_failure(proc->infiles[i], NULL, 1));
			continue ;
		}
		fd = open(proc->infiles[i], O_RDONLY);
		if (fd < 0)
			return (!report_failure(proc->infiles[i], NULL, 1));
		close(fd);
	}
	i--;
	fd = open(proc->infiles[i], O_RDONLY);
	if (fd < 0)
		return (!report_failure(proc->infiles[i], NULL, 1));
	proc->fd[FD_IN] = dup(fd);
	if (proc->fd[FD_IN] < 0)
		return (!report_failure(proc->infiles[i], NULL, 1));
	close(fd);
	//if signal hd_buf remains
	if (proc->flag_heredoc)
		!unlink(proc->infiles[i]) || report_failure(proc->infiles[i], NULL, 1);
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
	if (!deal_outfiles(proc))
		return (0);
	if (!deal_infiles(proc))
		return (0);
	return (1);
}
