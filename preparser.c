#include "parser.h"

/*
void	splitter(char *str)
{
	t_flags flag;
	struct s_args args;
	t_list *list;
	int i;

	i = -1;
	ft_bzero(&flag, sizeof(t_flags));
	ft_bzero(&args, sizeof(struct s_args));
	//args = ft_calloc(sizeof(t_args), 1);
	list = ft_lstnew(&args);
	//args.args = ft_strdup("amhere");
	
	while (str[++i])
	{
		write(1, "1\n", 2);
		if (str[i] == '\'')
			flager(&flag, 1);
		if (str[i] == '\"')
			flager(&flag, 2);
		if (str[i] == ' ' && flag.dq == 0 && flag.q == 0 && flag.cmd == 0)
		{
			args.cmd = ft_substr(str, 0, i);
			//list->content = malloc(sizeof(t_args));
			ft_lstadd_back(&list, ft_lstnew(&args));
			// args->next = ft_lstadd_back();
			flag.cmd = 1;
		}
	}
	printf("%s\n", ((struct s_args *)(list->content))->cmd);
	//printf("%s\n", ((struct s_args *)(list->content))->args);
	//printf("cmd: %s\n", args.cmd);
}
*/

static void flager(t_flags *flag, int numquotes)
{
	if (numquotes == 1)
		flag->q += 1;
	if (numquotes == 2)
		flag->dq += 1;
	if (numquotes == 3)
		flag->q += 1;
}

void	cmdsplitter(char *str)
{
	t_flags flag;
	t_args args;
	t_list *list;
	int i;

	i = -1;
	ft_bzero(&flag, sizeof(t_flags));
	while (str[++i])
	{
		if (str[i] == '\'')
			flager(&flag, 1);
		if (str[i] == '\"')
			flager(&flag, 2);
		if ((str[i] == ' ' || str[i] == '\0') && flag.dq == 0
			&& flag.q == 0 && flag.cmd == 0)
		{
			args.cmd = ft_substr(str, 0, i);
			flag.cmd = 1;
			if (str[i] == '\0')
				return;
			// ft_lstadd_back(&list, ft_lstnew(&args));
			argsplitter(str, args, flag, i);
		}
	}
	// printf("|__%s__|\n", ((struct s_args *)(list->content))->cmd);
}

void	argsplitter(char *str, t_args args, t_flags flag, int i)
{
	int n;

	if (flag.q == 0 && flag.dq == 0 && str[i]
		&& (str[i] == ' ' || str[i] == '\t'))
		{
			i = skipspaces(str, i);
			flager(&flag, 3);
		}
	n = i;
	while(str[++i])
	{
		if (str[i] == '\'' && flag.dq == 0 && str[i - 1] != '\\')
			flager(&flag, 1);
		if (str[i] == '\"' && flag.q == 0 && str[i - 1] != '\\')
			flager(&flag, 2);
		if ((str[i] == ' ' || str[i] == '\t')
			&& (flag.q == 1 || flag.dq == 1))
			continue;
		if ((str[i] == ' ' || str[i] == '\t' || str[i] == '\0')
			&& str[i - 1] != '\\' && (flag.q == 0 || flag.dq == 0))
			flager(&flag, 3);
		if ((flag.space == 1 || flag.dq == 1 || flag.q == 1)
			&& flag.args == 0)
			continue;
		if (flag.space == 2 || flag.dq == 2 || flag.q == 2)
		{
			args.args = ft_substr(str, n, i);
			flag.args = 1;
			// if (str[i] == '\0')
			// 	return;
		}
	}
}
