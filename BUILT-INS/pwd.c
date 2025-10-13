#include "../PARSING/INCLUDES/token.h"

void    ft_pwd(char **args)
{
  //  char    *var;
    char    *current;
    (void) args;
    current = getcwd(NULL, 0);
    if (current)
        printf("%s\n", current);
   /* else
    {
        var = getenv("PWD");
        printf("%s\n", var);
    }
    */
}