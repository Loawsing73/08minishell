/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erandjel <erandjel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:00:52 by erandjel          #+#    #+#             */
/*   Updated: 2025/09/12 15:34:51 by erandjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../token.h"

ssize_t	get_index(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '|')
			return (i);
		i++;
	}
	return (-1);
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

char	**ft_split_pipe(char *s)
{
	char	**tab;
	size_t	j;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * 4);
	if (!tab)
		return (NULL);
	tab[0] = ft_substr(s, 0, get_index(s));
	tab[1] = ft_substr(s, get_index(s), 1);
	tab[2] = ft_substr(s, get_index(s)+1, ft_strlen(s)-get_index(s)-1);
	j = 0;
	while (j < 3)
	{
		if (!tab[j])
		{
			free_all(tab, j);
			return (NULL);
		}
		j++;
	}
	tab[3] = NULL;
	return (tab);
}
