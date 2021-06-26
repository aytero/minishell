#include "parser.h"

static void flager(t_flags *flag, int numquotes)
{
	if (numquotes == 1 && flag->q == 0)
		flag->q = 1;
	if (numquotes == 1 && flag->q == 1)
		flag->q = 0;
	if (numquotes == 2 && flag->dq == 0)
		flag->q = 1;
	if (numquotes == 2 && flag->dq == 1)
		flag->q = 0;
}

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
