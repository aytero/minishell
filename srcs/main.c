#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// static char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	unsigned int	i;
// 	char			*s_sub;
// 	unsigned int	len_s;

// 	if (!s)
// 		return (NULL);
// 	len_s = strlen(s);
// 	if (start > len_s)
// 		start = len_s;
// 	if (len > len_s - start)
// 		len = len_s - start;
// 	s_sub = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!s_sub)
// 		return (NULL);
// 	i = 0;
// 	while (i < len && s[start + i])
// 	{
// 		s_sub[i] = s[start + i];
// 		i++;
// 	}
// 	s_sub[i] = '\0';
// 	return (s_sub);
// }

typedef struct s_flags
{
	int				dq;
	int				q;
	int				rdout;
	int				rdin;
	char			*filefd;
	int				sp;
}					t_flags;

static void zanulyator(t_flags *flag)
{
	flag->dq = 0;
	flag->q = 0;
	flag->rdin = 0;
	flag->rdout = 0;
	flag->sp = 0;
	flag->filefd = 0;
}

static char *zanuleniestroki(char *str, int i, int n)
{
	while (i-- < n)
		str[i] = ' ';
	return(str);
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

void cut_redir(char *str)
{
	t_flags *flag;
	int i;
	int n;

	n = 0;
	i = -1;
	zanulyator(flag);
	while (str[++i])
	{
		while (str[i] == '>' || str[i] == '<')
		{
			str = typeredir(str, i, flag);
			i++;//oshibka maybe zdes, esli budet
		}
		// printf("rdin = %d\nrdout = %d\n", flag->rdin, flag->rdout);
		n = i;
		while (str[i] != ' ' && str[i])
			i++;
		flag->filefd = ft_substr(str, n, i - n);// mb +1 nado v last perememnnoi
		str = zanuleniestroki(str, i, n);
		// printf("filename: |%s|\n", flag->filefd);
		
	}
}
