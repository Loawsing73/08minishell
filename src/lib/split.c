#include "../../includes/minishell.h"

static size_t	count_words(char *s, char set)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == set)
			i++;
		if (s[i] && s[i] != set)
		{
			count++;
			while (s[i] && s[i] != set)
				i++;
		}
	}
	return (count);
}

static char	*sub_split(char *s, char set, size_t *i)
{
	unsigned int	start;
	size_t			len;

	len = 0;
	start = *i;
	while (s[*i] && s[*i] == set)
		(*i)++;
	start = *i;
	while (s[*i] && s[*i] != set)
	{
		(*i)++;
		len++;
	}
	return (ft_substr(s, start, len));
}

static void	free_all(char	**tab, size_t j)
{
	while (j > 0)
	{
		j--;
		free(tab[j]);
		tab[j] = NULL;
	}
	free (tab);
	tab = NULL;
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	size_t	j;
	size_t	i;
	char	**tab;

	if (!s)
		return (NULL);
	words = count_words((char *)s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	j = 0;
	i = 0;
	while (j < words)
	{
		tab[j] = sub_split((char *)s, c, &i);
		if (!tab[j])
		{
			free_all(tab, j);
			return (NULL);
		}
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
