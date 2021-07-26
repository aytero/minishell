#include "parser.h"

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
	int		i;

	//count redirects and make arrays with types and filenames
	// aren't where max 2 redirs? so keep vars for in and out
	// bash chooses only last redir from its io type
	// ex. < file grep str < ttt < file – will read from last < file
	// though mult output rds create files but write only into last
	//int		rd_in_nbr = 0;
	//int		rd_out_nbr = 0;
	//add check for <<< and other
	//rd_in_nbr = count_elems(cmd_line, "<") - 1;//not suitable for redirs, doesn't detect str[0] == rd
	//rd_out_nbr = count_elems(cmd_line, ">") - 1;
	//DEBUG_PARSER && printf(GREY"rd_in_nbr %d\trd_out_nbr %d"RESET, rd_in_nbr, rd_out_nbr);
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
	}
	return (cmd_line);
}
