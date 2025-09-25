#include "../token.h"

char	*ft_strdup(char *s1)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = ft_strlen(s1);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
