#include "parser.h"

int	_print_all_rd(t_proc *proc)
{
	int		i;

	i = -1;
	while (++i < proc->rd_in_nbr)
	{
		printf(GREY"infile[%d] = |%s|"RESET, i, proc->infiles[i]);
		printf(GREY"infile[%d] type = %d"RESET, i, proc->rd_in_type[i]);
	}
	i = -1;
	while (++i < proc->rd_out_nbr)
	{
		printf(GREY"outfile[%d] = |%s|"RESET, i, proc->outfiles[i]);
		printf(GREY"outfile[%d] type = %d"RESET, i, proc->rd_out_type[i]);
	}
	//printf(GREY""RESET);
	return (1);
}

char	*cut_redir(char *cmd_line, int i, int type, int *io, t_proc *proc)
{
	int		file_index;
	char	*tmp;
	char	*tmp1;

	tmp = ft_substr(cmd_line, 0, i);

	i = skip_symbs(cmd_line, i, "> <\n\f\v\r\t");
	file_index = i;

	while (cmd_line[i] && !ft_strchr(" \n\f\v\r\t", cmd_line[i]))
		i++;
	if (type % 2)
	{
		proc->rd_out_type[*io] = type;
		proc->outfiles[(*io)++] = ft_substr(cmd_line, file_index, i - file_index);
	}
	else
	{
		proc->rd_in_type[*io] = type;
		proc->infiles[(*io)++] = ft_substr(cmd_line, file_index, i - file_index);
	}
	tmp1 = ft_strdup(cmd_line + i);
	free(cmd_line);
	cmd_line = ft_strjoin(tmp, tmp1);
	free(tmp);
	free(tmp1);
//	printf("flag %d\n", O_RDONLY);
//	printf("flag %d\n", O_WRONLY | O_TRUNC | O_CREAT);
//	printf("flag %d\n", O_WRONLY | O_APPEND | O_CREAT);
//	printf("cmd |%s|\n", cmd_line);
//	printf("file |%s|\n", file);
	//proc->flag_redir = 1;
	return (cmd_line);
}

char	*parse_redir(char *cmd_line, t_proc *proc)
{
	int		i;
	int		out;
	int		in;

	// |< file|	- seg f
	//count redirects and make arrays with types and filenames
	// aren't where max 2 redirs? so keep vars for in and out
	// bash chooses only last redir from its io type
	// ex. < file grep str < ttt < file – will read from last < file
	// though mult output rds create files but write only into last

	proc->rd_in_nbr = count_elems(cmd_line, "<") - 1;
	proc->rd_out_nbr = count_elems(cmd_line, ">") - 1;
	DEBUG_PARSER && printf(GREY"rd_in_nbr %d\trd_out_nbr %d"RESET, proc->rd_in_nbr, proc->rd_out_nbr);

	if (proc->rd_out_nbr)
		proc->flag_pipe = 0;
	if (proc->rd_out_nbr || proc->rd_in_nbr)
		proc->flag_redir = 1;
	
	//maybe get only last INfile and all OUTfiles
	proc->rd_in_nbr && (proc->infiles = malloc(sizeof(char *) * (proc->rd_in_nbr + 1)));
	if (proc->rd_in_nbr && !proc->infiles)
		return (NULL);
	proc->rd_out_nbr && (proc->outfiles = malloc(sizeof(char *) * (proc->rd_out_nbr + 1)));
	if (proc->rd_out_nbr && !proc->outfiles)
		return (NULL);
	proc->rd_in_nbr && (proc->rd_in_type = malloc(sizeof(int *) * proc->rd_in_nbr));
	if (proc->rd_in_type && !proc->rd_in_type)
		return (NULL);
	proc->rd_out_nbr && (proc->rd_out_type = malloc(sizeof(int *) * proc->rd_out_nbr));
	if (proc->rd_out_type && !proc->rd_out_type)
		return (NULL);
	//printf(GRN"%s"RESET, cmd_line);
	//(void)proc;

	!(out = 0) && (in = 0);// && (i = -1);
	i = -1;
	while (cmd_line[++i])
	{
		if (cmd_line[i] == '>' && cmd_line[i + 1] == '>')
			cmd_line = cut_redir(cmd_line, i, DB_REDIR_OUT, &out, proc);
		else if (cmd_line[i] == '<' && cmd_line[i + 1] == '<')
			(cmd_line = cut_redir(cmd_line, i, DB_REDIR_IN, &in, proc)) && (proc->flag_heredoc = 1);
		else if (cmd_line[i] == '<' && cmd_line[i + 1] != '<')
			cmd_line = cut_redir(cmd_line, i, REDIR_IN, &in, proc);
		else if (cmd_line[i] == '>' && cmd_line[i + 1] != '>')
			cmd_line = cut_redir(cmd_line, i, REDIR_OUT, &out, proc);
	}
	return (cmd_line);
}
