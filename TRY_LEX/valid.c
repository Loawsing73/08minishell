#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	special_caract(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\\' || input[i] == ';' || input[i] == '*' ||
			input[i] == '[' || input[i] == ']' || input[i] == '(' ||
			input[i] == '#' || input[i] == '=' ||
			input[i] == '%' || input[i] == '!')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_quote(char *s, int *i)
{
	(*i)++;
	while (s[*i])
	{
		if (s[*i] == '\'')
			return (1);
		(*i)++;
	}
	return (0);
}

static int	ft_dquote(char *s, int *i)
{
	(*i)++;
	while (s[*i])
	{
		if (s[*i] == '"')
			return (1);
		(*i)++;
	}
	return (0);
}

int	valid_input(char *input)
{
	int	i;
	int	quote;
	int	dquote;

	i = 0;
	dquote = 1;
	quote = 1;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			quote = ft_quote(input, &i);
			i++;
		}
		else if (input[i] == '"')
		{
			dquote = ft_dquote(input, &i);
			i++;
		}
		else
			i++;
	}
	return (special_caract(input) * quote * dquote);
}

/*
int main()
{
    char *input;
    input = readline("enter : ");
    if (!input)
        return (1);
    printf("%d\n", valid_input(input));
    free(input);
    
    return (0);
}
*/
