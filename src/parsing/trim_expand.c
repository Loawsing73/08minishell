#include "../../includes/minishell.h"

//gardera index a jour 
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
/*
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
*/

static int	expand_variable(char *s, char *d, int *i, int *j, t_env *env)
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
		var_value = get_var(var_name, env);
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

static void	filldquote(char *s, char *d, int *i, int *j, t_env *env)
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

static int	max_env(t_env *env, char *s)
{
	int	max;

	max = 0;
	if (!env)
		return (ft_strlen(s));
	while (env)
	{
		if (max < ft_strlen(env->value))
			max = ft_strlen(env->value);
		env = env->next;
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
/*fonction principale de parsing:
*/
char	*concate_hell(char *expanded_input, t_global *global)
{
	int i;
	int j;
	char *stash;
	
	i = 0;
	j = 0;
	stash = malloc(sizeof(char) * max_env(global->env, expanded_input));
	if (!stash)
		return (NULL);
	while (expanded_input[i])
	{
		if ((expanded_input[i] == '<' || expanded_input[i] == '>') && consecutive_angbra(expanded_input, i))
			expand_heredoc(expanded_input, stash, &i, &j);
		else if (expanded_input[i] == '\'' || expanded_input[i] == '"')
		{
			if (expanded_input[i] == '\'')
				fillquote(expanded_input, stash, &i, &j);
			else if (expanded_input[i] == '"')
				filldquote(expanded_input, stash, &i, &j, global->env);
		}
		else if (expanded_input[i] == '$' && !consecutive_dollar(expanded_input, i))
		{
			if (!expand_variable(expanded_input, stash, &i, &j, global->env))
				fill(expanded_input, stash, &i, &j);
		}
		else
		{
        	if (expanded_input[i] == '$' && consecutive_dollar(expanded_input, i))
            	fill(expanded_input, stash, &i, &j);
        	fill(expanded_input, stash, &i, &j);
		}
    }
	stash[j] = '\0';
	return (stash);
}
