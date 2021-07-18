#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;
	char	*str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (len1--)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (len2--)
		str[i++] = s2[j++];
	str[i] = '\0';
	free((void *)s1);
	return (str);
}