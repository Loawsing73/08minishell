#include "token.h"

static char *get_dollar(char *s)
{
        int i = 0;
        if (get_index(i, s, '$') < 280300 && s[i] != '$')
        {    
            i = get_index(i, s, '$') + 1; 
            return (&s[i]);
        }
        else
            return (NULL);
}
char *get_variable(char **env, char *s)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (!get_dollar(s))
            return (NULL);
        if ((ft_strncmp(get_dollar(s), env[i], get_index(0, env[i], '='))) == 0)
            return (env[i]);
        i++;
    }
    return (NULL);
}
char *get_depend(char *s)
{
    char    *depend;
    int     i;
    int     j;

    depend = malloc(sizeof(char) * (ft_strlen(s)-get_index(0, s, '=')+1));
    i = get_index(0, s, '=') + 1;
    j = 0;
    while (s[i])
    {
       depend[j] = s[i];
       i++;
       j++; 
    }
    depend[j] = '\0';
    return (depend);
}
// int main(int c, char **ag, char **env)
// {
//     char *s = "echo $VSCODE_GIT_ASKPASS_NODE";
//     char *var = get_variable(env, s);
//     printf("%s\n", get_depend(var));
// }