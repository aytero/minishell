#include "parser.h"

int	count_redirs(char *str, char type)
{
	int		i;
	int		nbr;
	char	div[2];

	nbr = 0;
	i = 0;
	while (str[i])
	{
		i = if_quotes(str, i);
		if (str[i] == type)//type
		{
			nbr++;
			div[0] = type;
			div[1] = '\0';
			i = skip_symbs(str, i, div);
			continue ;
		}
		i++;
	}
	return (nbr);
}

char	*cut_redir(char *cmd_line, int i, int type, t_proc *proc)
{
	int		file_index;
	//char	*file;
	char	*tmp;
	char	*tmp1;

	tmp = ft_substr(cmd_line, 0, i);
	while (cmd_line[i] == '>' || cmd_line[i] == '<' || cmd_line[i] == ' ')
		i++;
	file_index = i;
	while (cmd_line[i] && cmd_line[i] != ' ')
		i++;
	proc->filename = ft_substr(cmd_line, file_index, i - file_index);
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
	proc->type_redir = type;
	proc->flag_redir = 1;
	//deal_redir(proc->filename, type, proc);
	return (cmd_line);
}

char	*parse_redir(char *cmd_line, t_proc *proc)
{
	//int		i;

	// |< file|	- seg f
	//count redirects and make arrays with types and filenames
	// aren't where max 2 redirs? so keep vars for in and out
	// bash chooses only last redir from its io type
	// ex. < file grep str < ttt < file – will read from last < file
	// though mult output rds create files but write only into last
//	int		rd_in_nbr = 0;
//	int		rd_out_nbr = 0;
	proc->rd_in_nbr = count_redirs(cmd_line, '<');
	proc->rd_out_nbr = count_redirs(cmd_line, '>');
	DEBUG_PARSER && printf(GREY"rd_in_nbr %d\trd_out_nbr %d"RESET, proc->rd_in_nbr, proc->rd_out_nbr);
	(void)proc;
	/*
	proc->rd_in_nbr && (proc->infiles = malloc(sizeof(char *) * (proc->rd_in_nbr + 1)));
	if (!proc->infiles)
		return (NULL);
	//maybe get only last OUTfile and all infiles
	proc->rd_out_nbr && (proc->outfiles = malloc(sizeof(char *) * (proc->rd_out_nbr + 1)));
	if (!proc->outfiles)
		return (NULL);
	i = -1;
	while (cmd_line[++i])
	{
		if (cmd_line[i] == '>' && cmd_line[i + 1] == '>')
			cmd_line = cut_redir(cmd_line, i, DB_REDIR_OUT, proc);
		else if (cmd_line[i] == '<' && cmd_line[i + 1] == '<')
			cmd_line = cut_redir(cmd_line, i, DB_REDIR_IN, proc);
		else if (cmd_line[i] == '<' && cmd_line[i + 1] != '<')
			cmd_line = cut_redir(cmd_line, i, REDIR_IN, proc);
		else if (cmd_line[i] == '>' && cmd_line[i + 1] != '>')
			cmd_line = cut_redir(cmd_line, i, REDIR_OUT, proc);
	}*/
	return (cmd_line);
}
