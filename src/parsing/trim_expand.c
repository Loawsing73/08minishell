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

static int	expand_variable(char *s, char *d, t_indexx *i, t_env *env)
{
	char	*var_name;
	char	*var_value;

	if (s[i->i] != '$' || s[(i->i) + 1] == '$')
		return (0);
	var_name = extract_variable_input(s, i->i + 1); // free var_name
	if (var_name)
	{
		var_value = get_var(var_name, env);
		if (var_value)
		{
			while (var_value[++(i->k)])
			{
				d[i->j] = var_value[i->k];
				(i->j)++;
			}
			i->i = skip_variable(s, i->i + 1);
		}
		else
		{
			d[i->j] = ' ';
			i->i = skip_variable(s, i->i + 1);
		}
		return (free(var_name), 1);
	}
	return (0);
}

static void	filldquote(char *s, char *d, t_indexx *i, t_env *env)
{
	int	limit;

	(i->i)++;
	limit = get_index(i->i, s, '"');
	while ((i->i) < limit)
	{
		if (s[i->i] == '$' && s[(i->i) + 1] != '$')
		{
			if (!expand_variable(s, d, i, env))
			{
				d[i->j] = -s[i->i];
				(i->j)++;
				(i->i)++;
			}
		}
		else
		{
			d[i->j] = -s[i->i];
			(i->j)++;
			(i->i)++;
		}
	}
	(i->i)++;
}

static void	fill_exp_dquote(char *s, char *d, t_indexx *i)
{
	int	limit;

	(i->i)++;
	limit = get_index(i->i, s, '"');
	while ((i->i) < limit)
	{
		d[i->j] = -s[i->i];
		(i->j)++;
		(i->i)++;
	}
	(i->i)++;
}

static void fillquote(char *s, char *d, t_indexx *i)
{
	(i->i)++;
	while (s[i->i] != '\'' && s[i->i])
	{
		if (s[i->i] == '>' || s[i->i] == '<' || s[i->i] == '|')
			d[i->i] = -s[i->i];
		else
			d[i->j] = s[i->i];
		(i->i)++;
		(i->j)++;
	}
	(i->i)++;
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

static void	fill(char *s, char *d, t_indexx *i)
{
	d[i->j] = s[i->i];
	(i->i)++;
	(i->j)++;
}

static void	expand_heredoc(char *s, char *d, t_indexx *i)
{
	fill(s, d, i);
	fill(s, d, i);
	while (s[i->i] == ' ')
		(i->i)++;
	while ((i->i) != get_space(i->i, s))
	{
		if (s[i->i] == '\'')
			fillquote(s, d, i);
		else if (s[i->i] == '"')
			fill_exp_dquote(s, d, i);
		else
			fill(s, d, i);
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
	t_indexx	i;
	char		*stash;
	
	i.i = 0;
	i.j = 0;
	i.k = -1;
	stash = malloc(sizeof(char) * max_env(global->env, expanded_input)); //free stash
	if (!stash)
		return (NULL);
	while (expanded_input[i.i])
	{
		if ((expanded_input[i.i] == '<' || expanded_input[i.i] == '>') && consecutive_angbra(expanded_input, i.i))
			expand_heredoc(expanded_input, stash, &i);
		else if (expanded_input[i.i] == '\'' || expanded_input[i.i] == '"')
		{
			if (expanded_input[i.i] == '\'')
				fillquote(expanded_input, stash, &i);
			else if (expanded_input[i.i] == '"')
				filldquote(expanded_input, stash, &i, global->env);
		}
		else if (expanded_input[i.i] == '$' && !consecutive_dollar(expanded_input, i.i))
		{
			if (!expand_variable(expanded_input, stash, &i, global->env))
				fill(expanded_input, stash, &i);
		}
		else
		{
        	if (expanded_input[i.i] == '$' && consecutive_dollar(expanded_input, i.i))
            	fill(expanded_input, stash, &i);
        	fill(expanded_input, stash, &i);
		}
    }
	stash[i.j] = '\0';
	return (stash);
}
