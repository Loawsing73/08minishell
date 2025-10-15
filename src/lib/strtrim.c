#include "../../includes/minishell.h"

static unsigned int	ft_enter(char *s, char *set)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (set[j])
		{
			if (s[i] == set[j])
			{
				i++;
				j = 0;
			}
			else
				j++;
		}
		return (i);
	}
	return (i);
}

static size_t	ft_exit(char *s, char *set)
{
	size_t	len;
	size_t	j;

	len = (ft_strlen(s) - 1);
	j = 0;
	while (s[len])
	{
		while (set[j])
		{
			if (s[len] == set [j])
			{
				len--;
				j = 0;
			}
			else
				j++;
		}
		return (len);
	}
	return (len);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	trimmed = ft_substr(s1, ft_enter(s1, set), ft_exit(s1, set)
			- ft_enter(s1, set) + 1);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}
