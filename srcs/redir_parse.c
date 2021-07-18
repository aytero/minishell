#include "parser.h"

static void zanulyator(t_flags *flag)
{
	flag->dq = 0;
	flag->q = 0;
	flag->rdin = 0;
	flag->rdout = 0;
	flag->sp = 0;
	flag->filefd = NULL;
}

static char *typeredir(char *str, int i, t_flags *flag)
{
	if (str[i] == '>')
	{
		flag->rdout++;
		str[i] = ' ';
	}
	if (str[i] == '<')
	{
		flag->rdin++;
		str[i] = ' ';
	}
	return(str);
}

void cut_redirr(char *str)
{
	t_flags *flag;
	int i;
	int n;

	n = 0;
	i = -1;
	zanulyator(&flag);
	while (str[++i])
	{
		while (str[i] == '>' || str[i] == '<')
		{
			str = typeredir(str, i, flag);
			i++;//oshibka maybe zdes, esli budet
		}
		printf("rdin = %d\nrdout = %d\n", flag->rdin, flag->rdout);
		n = i;
		while (str[i] != ' ' && str[i])
			i++;
		flag->filefd = ft_substr(str, n, i - n);// mb +1 nado v last perememnnoi
		printf("filename: |%s|\n", flag->filefd);
	}
}
