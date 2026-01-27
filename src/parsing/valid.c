#include "../../includes/minishell.h"

static int	is_valid_delimiter(char *s)
{
	int	i;

	i = get_index(0, s, '<');
	if (i >= 0)
	{
		if (s[++i] == '<')
		{
			i++;
			while (s[i] == ' ')
				i++;
			if (s[i] == '>' || s[i] == '<' || s[i] == '|')
				return (0);
		}
	}
	return (1);
}
/*s'assure qu'input finit ou commence pas par |*/
static int	operator_end_beg(char *s)
{
	if (s[0] == '|' || s[ft_strlen(s)-1] == '|')
		return (0);
	if (s[ft_strlen(s)-1] == '<' || s[ft_strlen(s)-1] == '>')
		return (0);
	return (1);
}
/*peut pas avoir "> >"*/
static int	far_angbra(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '<' && s[i + 1] == ' ')
		{
			if (s[i + 2] == '<')
				return (0);
			if (s[i + 2] == '>')
				return (0);
		}
		if (s[i] == '>' && s[i + 1] == ' ')
		{
			if (s[i + 2] == '<')
				return (0);
			if (s[i + 2] == '>')
				return (0);
		}
	}
	return (1);
}
/*peut pas ">>>" ou "<<<"*/
static int	triple_angbra(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if ((s[i] == '<' && s[i + 1] == '<')
			|| (s[i] == '>' && s[i + 1] == '>'))
		{
			if (s[i + 2] == '<')
				return (0);
			if (s[i + 2] == '>')
				return (0);
			if (s[i + 2] == '|')
				return (0);
		}
		if (s[i] == '>' && s[i + 1] == '<')
			return (0);
		if (s[i] == '<' && s[i + 1] == '>')
			return (0);
	}
	return (1);
}

/*s'assure que quote bien fermée*/
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
/*s'assure que dquote bien fermée*/
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
	return (quote * dquote * operator_end_beg(input)
		* triple_angbra(input) * far_angbra(input) * is_valid_delimiter(input));
}
