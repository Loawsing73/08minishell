#include "../../includes/minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = NULL;
	while (1)
	{
		if (*s == (char)c)
			last = (char *)s;
		if (*s == '\0')
			break ;
		s++;
	}
	return (last);
}
