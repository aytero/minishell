#include "libft.h"

char	*ft_strjoin_sep(char *s1, char *s2, char sep)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	str[i++] = sep;
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
