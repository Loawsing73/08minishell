#include "../../includes/minishell.h"

//gardera index a jour 
#include "../INCLUDES/token.h"

static int	skip_variable(char *s, int i)
{
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	return (i);
}

static char	*extract_variable_input(char *s, int start_pos)
{
	int		i;
	int		len;
	char	*var_name;

	i = start_pos;
	len = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
	{
		len++;
		i++;
	}
	if (len == 0)
		return (NULL);
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
	i = 0;
	while (i < len)
	{
		var_name[i] = s[start_pos + i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

static char	*find_within_env(char **env, char *var_name)
{
	int	i;
	int	var_len;

	if (!env || !var_name)
		return (NULL);
	i = 0;
	var_len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(var_name, env[i], var_len) == 0
			&& env[i][var_len] == '=')
			return (&env[i][var_len + 1]);
		i++;
	}
	return (NULL);
}

static int	expand_variable(char *s, char *d, int *i, int *j, char **env)
{
	char	*var_name;
	char	*var_value;
	int		k;
	int		var_start;

	if (s[*i] != '$' || s[(*i) + 1] == '$')
		return (0);
	var_start = *i + 1;
	var_name = extract_variable_input(s, var_start);
	if (var_name)
	{
		var_value = find_within_env(env, var_name);
		if (var_value)
		{
			k = -1;
			while (var_value[++k])
			{
				d[*j] = var_value[k];
				(*j)++;
			}
			*i = skip_variable(s, var_start);
		}
		else
		{
			d[*j] = ' ';
			*i = skip_variable(s, var_start);
		}
		return (free(var_name), 1);
	}
	return (0);
}

static void	filldquote(char *s, char *d, int *i, int *j, char **env)
{
	int	limit;

	(*i)++;
	limit = get_index(*i, s, '"');
	while ((*i) < limit)
	{
		if (s[*i] == '$' && s[(*i) + 1] != '$')
		{
			if (!expand_variable(s, d, i, j, env))
			{
				d[*j] = -s[*i];
				(*j)++;
				(*i)++;
			}
		}
		else
		{
			d[*j] = -s[*i];
			(*j)++;
			(*i)++;
		}
	}
	(*i)++;
}

static void	fill_exp_dquote(char *s, char *d, int *i, int *j)
{
	int	limit;

	(*i)++;
	limit = get_index(*i, s, '"');
	while ((*i) < limit)
	{
		d[*j] = -s[*i];
		(*j)++;
		(*i)++;
	}
	(*i)++;
}

static void fillquote(char *s, char *d, int *i, int *j)
{
	(*i)++;
	while (s[*i] != '\'' && s[*i])
	{
		if (s[*i] == '>' || s[*i] == '<' || s[*i] == '|')
			d[*i] = -s[*i];
		else
			d[*j] = s[*i];
		(*i)++;
		(*j)++;
	}
	(*i)++;
}

static int	max_env(char **env, char *s)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	if (!env || !env[i])
		return (ft_strlen(s));
	while (env[i])
	{
		if (max < ft_strlen(env[i]))
			max = ft_strlen(env[i]);
		i++;
	}
	return (max + 100);
}

static void	fill(char *s, char *d, int *i, int *j)
{
	d[*j] = s[*i];
	(*i)++;
	(*j)++;
}

static void	expand_heredoc(char *s, char *d, int *i, int *j)
{
	fill(s, d, i, j);
	fill(s, d, i, j);
	while (s[*i] == ' ')
		(*i)++;
	while ((*i) != get_space(*i, s))
	{
		if (s[*i] == '\'')
			fillquote(s, d, i, j);
		else if (s[*i] == '"')
			fill_exp_dquote(s, d, i, j);
		else
			fill(s, d, i, j);
	}
}

static int	consecutive_dollar(char *s, int i)
{
	i++;
	if (s[i] == '$')
		return (1);
	return (0);
}

static int	consecutive_angbra(char *s, int i)
{
	i++;
	if (s[i] == '>' || s[i] == '<')
		return (1);
	return (0);
}

char	*concate_hell(char *s, char **env)
{
	int i;
	int j;
	char *stash;
	
	i = 0;
	j = 0;
	stash = malloc(sizeof(char) * max_env(env, s));
	if (!stash)
		return (NULL);
	while (s[i])
	{
		if ((s[i] == '<' || s[i] == '>') && consecutive_angbra(s, i))
			expand_heredoc(s, stash, &i, &j);
		else if (s[i] == '\'' || s[i] == '"')
		{
			if (s[i] == '\'')
				fillquote(s, stash, &i, &j);
			else if (s[i] == '"')
				filldquote(s, stash, &i, &j, env);
		}
		else if (s[i] == '$' && !consecutive_dollar(s, i))
		{
			if (!expand_variable(s, stash, &i, &j, env))
				fill(s, stash, &i, &j);
		}
		else
		{
        	if (s[i] == '$' && consecutive_dollar(s, i))
            	fill(s, stash, &i, &j);
        	fill(s, stash, &i, &j);
		}
    }
	stash[j] = '\0';
	return (stash);
}
