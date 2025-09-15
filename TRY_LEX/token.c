#include "token.h"

int	got_pipe(char *s)
{
	int	i = 0;

	while (s[i])
	{
		if (s[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

t_token	get_token(char *s)
{
	if (!s)
		return (ERROR);
//	if (s[0] == '\'')
//		return (QUOTE);
//	else if (s[0] == '"')
//		return (DOUBLE_QUOTE);
	else if (s[0] == '<')
	{	
		if (s[1] == '<')
			return (D_LESS);
		return (LESS);
	}
	else if (s[0] == '>')
	{
		if (s[1] == '>')
			return (D_GREAT);
		return (GREAT);
	}
	else if (s[0] == '|')
		return (PIPE);
	else if (s[0] == '\n')
		return (NL);
	else
		return (WORD);
}

int	count_crate(char **s)
{
	int	j;
	int count;

	j = 0;
	count = 0;
	while (s[j])
	{
		if (ft_strlen(s[j]) > 0)
			count++;
		j++;
	}
	return (count);
}

int	count_crate_pipe(char **s)
{
	char	**pipe;
	char	**new;
	int		i;
	int		count;

	i = 0;
	count = count_crate(s);
	while (s[i])
	{	
		if (got_pipe(s[i]))
		{
			pipe = ft_split_pipe(s[i]);
			count = count + count_crate(pipe) - 1;
		}
		i++;
	}
	return (count);
}

char	**handle_pipe(char **s)
{
	int		i;
	int		j;
	int		k;
	char	**ag;
	char	**pipe;

	ag = malloc(sizeof(char *) * (count_crate_pipe(s) + 1));
	j = 0;
	while (s[j])
	{
			i = 0;
			if (!got_pipe(s[j]))
			{
				while (s[j][i])
				{
					printf("%d\n", j);
					printf("%d\n", i);
					ag[j] = malloc(sizeof(char) * (ft_strlen(s[j]) + 1));
					ag[j][i] = s[j][i];
					write(1, &ag[i][j], 1);
					i++;
				}
			}
			else
			{
				printf("j = %d\n", j);
				printf("%d\n", got_pipe(s[j]));
				pipe = ft_split_pipe(s[j]);
				k = 0;
				while (pipe[k])
				{
					ag[j] = malloc(sizeof(char) * (ft_strlen(pipe[k]) + 1));
					i = 0;
					while (pipe[k][i] && ft_strlen(pipe[k]) != 0)
					{
						printf("%d\n", i);
						ag[j][i] = pipe[k][i];
						printf("%c\n", ag[j][i]);
						i++;
					}
					k++;
				}
			}
		ag[j][i] = '\0';
		printf("%d\n", i);
		j++;
	
		}
	
	write(1, "\n m", 3);
	s[j] = NULL;
	return (ag);
}

int	main()
{
	
	int		i = 0;
	char	*input;
	t_token	token;
	char	**split;
	char	**pipe;

	input = readline("enter : ");
	if (got_pipe(input))
	{
		split = ft_split(input, ' ');
		pipe = handle_pipe(split);
		while (pipe[i])
		{
			printf("%s -", pipe[i]);
			token = get_token(pipe[i]);
			printf("%u\n", token);
			i++;
		}
	}
	else
	{
		split = ft_split(input, ' ');
		while (split[i] != NULL && split[i][0] != '\0')
		{
			token = get_token(split[i]);
			printf("%u - %s\n", token, split[i]);
			i++;
		}
	}
}
