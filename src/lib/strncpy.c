#include "../../includes/minishell.h"

void    ft_strncpy(char *d, char *s, int n)
{
    int i;

    i = 0;
    while(i < n)
    {
        d[i] = s[i];
        i++;
    }
}
