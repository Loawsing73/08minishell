#include "../../includes/minishell.h"

int	ft_atoi(const char *nptr)
{
	size_t	index;
	long	resultat;
	int		nega;

	if (!nptr)
		return (0);
	nega = 1;
	index = 0;
	while (nptr[index] == ' ' || nptr[index] == '\t' || nptr[index] == '\n'
		|| nptr[index] == '\v' || nptr[index] == '\f' || nptr[index] == '\r')
		index++;
	if (nptr[index] == '-')
	{
		nega = -1;
		index++;
	}
	else if ((nptr[index] == '+'))
		index++;
	resultat = 0;
	while (ft_isdigit(nptr[index]))
	{
		resultat = resultat * 10 + (nptr[index] - '0');
		index++;
	}
	return ((int)resultat * nega);
}
