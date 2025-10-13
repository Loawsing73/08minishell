#include "../token.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join_out;
	int	i;
	int	j;

	if (!s1 || !s2)
		return (NULL);
	join_out = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join_out)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join_out[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		join_out[i + j] = s2[j];
		j++;
	}
	join_out[i + j] = '\0';
	return (join_out);
}