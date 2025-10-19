#include "../../includes/minishell.h"

static int	size_tab(char **tab)
{
	int	x;

	x = 0;
	while (tab[x])
		x++;
	return (x);
}

static char	*join_value(char **tab, char c)
{
	char	*resultat;
	char	*tmp;
	char	sep[2];
	int		x;

	resultat = NULL;
	x = 1;
	sep[0] = c;
	sep[1] = '\0';
	while (tab[x])
	{
		if (!resultat)
			resultat = ft_strjoin(tab[x], sep);
		else
		{
			tmp = ft_strjoin(tab[x], sep);
			resultat = ft_strjoin(resultat, tmp);
			free(tmp);
		}
		x++;
	}
	return (resultat);
}

char	**split_env(char *str, char c)
{
	int		size;
	char	**resultat;
	char	**tab;
	char	*value;

	resultat = malloc(sizeof(char *) * 2);
	if (!resultat)
		return (NULL);
	tab = ft_split(str, c);
	if (!tab)
		return (NULL);
	size = size_tab(tab);
	if (size > 2)
		value = join_value(tab, c);
	else
		value = tab[1];
	resultat[0] = tab[0];
	resultat[1] = value;
	return (resultat);
}
