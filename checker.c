#include "parser.h"

static int	secondquot(char *str, char quot, int *i)
{
	int j;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == quot && *i > j)
			return (1);
	}
	return (0);
}

int	checker(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			if (secondquot(str, '\'', &i))
				return (1);
			else
				return (0);
		}
	}
	return (2);
	// slashlastsym(str);
}

int main(void)
{
	char *str = "str with one 'quot ";
	char *str2 = "str with two 'quotes'";
	if (checker(str) == 0)
		printf ("\n odna quota");
	else
		printf ("\n dve quotbl");
	if (checker(str2) == 0)
		printf ("\n odna quota");
	else
		printf ("\n dve quotbl");

}