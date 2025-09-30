/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erandjel <erandjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:00:44 by erandjel          #+#    #+#             */
/*   Updated: 2025/09/25 19:18:14 by erandjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../token.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*sub;
	int	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	else if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (s[start + i] < 0)
			s[start + i] = -s[start + i];
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
