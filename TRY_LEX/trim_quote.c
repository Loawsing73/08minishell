#include "token.h"

static int max_env(char **env, char *s)
{
  int i;
  int max;

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
  return (max);
}
static void fillquote(char *s, char *d, int *i, int *j)
{
  (*i)++;
  while (s[*i] != '\'' && s[*i])
  {
    d[*j] = s[*i];
    (*i)++;
    (*j)++;
  }
  (*i)++;
}
static int is_caps(char *s, int i)
{
  while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
        i++;
    return i;
}
static char *extract_var_name(char *s, int start_pos)
{
    int i = start_pos;
    int len = 0;
    char *var_name;
    
    while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
    {
        len++;
        i++;
    }
    if (len == 0)
        return NULL;
    var_name = malloc(sizeof(char) * (len + 1));
    if (!var_name)
        return NULL;
    i = 0;
    while (i < len)
    {
        var_name[i] = s[start_pos + i];
        i++;
    }
    var_name[i] = '\0';
    return var_name;
}
static void filldquote(char *s, char *d, int *i, int *j, char **env)
{
    char *var_name;
    char *var_value;
    int k;
    int var_start;
    
    while (++(*i) < get_index(*i, s, '"'))
    {
        if (s[*i] == '$' && s[(*i)+1] != '$')
        {
            // Extract variable name at current position
            var_start = *i + 1; // Position after $
            var_name = extract_var_name(s, var_start);
            if (var_name)
            {
                var_value = get_variable(env, var_name);
                if (var_value)
                {
                    k = 0;
                    while (var_value[k])
                    {
                        d[*j] = var_value[k];
                        (*j)++;
                        k++;
                    }
                }
                
                // Skip past the variable name
                *i = is_caps(s, var_start) - 1; // -1 because loop will increment
                free(var_name); // Clean up allocated memory
            }
            else
            {
                // No valid variable name, treat $ as literal
                d[*j] = s[*i];
                (*j)++;
            }
        }
        else
        {
            d[*j] = s[*i];
            (*j)++;
        }
    }
    (*i)++; // Skip closing quote
}

char    *concate_hell(char *s, char **env)
{
    int        i;
    char    *stash;
    int        j;
    
    i = 0;
    j = 0;
    stash = malloc(sizeof(char) * (max_env(env, s) + ft_strlen(s)));
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '"')
        { 
          if (s[i] == '"')
            filldquote(s, stash, &i, &j, env);
          else if (s[i] == '\'')
            fillquote(s, stash, &i, &j);
        }
        else
        { 
          stash[j] = s[i];
          i++;
          j++;
        }
    }
    stash[j] = '\0';
    return (stash);
}

