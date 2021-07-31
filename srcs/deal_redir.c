#include "execute.h"

int	deal_here_doc(t_proc *proc, int i)
{
	int		fd;
	char	*str;

	fd = -1;
	fd = open("heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (!report_failure(NULL, "open", 1));//return

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
	return (1);
}

int	deal_redir(t_proc *proc)
{
	int		fd;
	int		i;
	int		flags[4];

	flags[0] = O_RDONLY;
	flags[1] = O_WRONLY | O_TRUNC | O_CREAT;
	flags[2] = -1;
	flags[3] = O_WRONLY | O_APPEND | O_CREAT;
	fd = -1;
	i = -1;
	while (++i < proc->rd_in_nbr)
	{
		if (proc->rd_in_type[i] == 2)
		{
			deal_here_doc(proc, i);
			continue ;
		}
		fd = open(proc->infiles[i], flags[proc->rd_in_type[i]]);
		if (fd < 0)
			return (!report_failure(NULL, "open", 1));//
		if (i == proc->rd_in_nbr - 1)
		{
			proc->fd[FD_IN] = dup(fd);
			//if (dup2(fd, proc->fd[FD_IN]) < 0)
			//	return (!report_failure(NULL, "dup2", 1));
		}
		close(fd);
	}
	i = -1;
	while (++i < proc->rd_out_nbr)
	{
		fd = open(proc->outfiles[i], flags[proc->rd_out_type[i]], 0644);
		if (fd < 0)
			return (!report_failure(NULL, "open", 1));//return
		if (i == proc->rd_out_nbr - 1)
		{
			proc->fd[FD_OUT] = dup(fd);
			//if (dup2(fd, proc->fd[FD_OUT]) < 0)
			//	return (!report_failure(NULL, "dup2", 1));
		}
		close(fd);
	}
	if (proc->flag_heredoc)
	{
		fd = open("heredoc", O_RDONLY);
		if (fd < 0)
			return (!report_failure(NULL, proc->cmd, 1));//cannot exit bc of builtins
		//if (dup2(fd, proc->fd[FD_IN]) < 0)
		//	return (!report_failure(NULL, proc->cmd, 1));
		proc->fd[FD_IN] = dup(fd);
		close(fd);
		//if signal hd_buf remains
		!unlink("heredoc") || report_failure(NULL, "unlink", 1);
	}
	return (1);
}

