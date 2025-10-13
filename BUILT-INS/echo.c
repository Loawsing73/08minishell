#include "../PARSING/INCLUDES/token.h"

static int flag_n(char *arg)
{
    int i;

    i = 2;
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

void ft_echo(char **args)
{
	int i;
	int flag;
	int printed;
	
	i = 0;
	flag = 0;
	printed = 0;
	if (!args || !args[1])
	{
		printf("\n");
		return ;
	}
	while (args[++i] && ft_strncmp(args[i], "-n", 2) == 0 && flag_n(args[i]))	
        flag = 1;
    while (args[i])
	{
		if (printed)
			printf(" ");
		printf("%s", args[i]);
		printed = 1;
        i++;
	}
	if (!flag)
		printf("\n");
}
