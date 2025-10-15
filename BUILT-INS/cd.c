#include "../PARSING/INCLUDES/token.h"

void	ft_cd(char **args, char **env)
{
	(void)args;
	printf("env test %s\n", env[0]);
	printf("Buil-in cd\n");
}

/*static int get_rindex(char *path)
{
    int i;
    
    i = ft_strlen(path);
    while(i >= 0)
    {
        if (path[i] == '/')
            return (i);
        i--;
    }
    return (-1);
}

void ft_cd(char **args)
{
    char *dir;
    char *prev;
    int rindex;
    int status;
    
    
    status = 0;
    if (!args)
        return ;
    if (!args[1])
    {
        status = chdir(getenv("HOME"));
        return ;
    }
    if (ft_strncmp(args[1], "..", 2) == 0)
    {
        dir = getcwd(NULL, 0);
        printf("%s\n", dir);
        if (!dir)
        {
            perror("getcwd");
            return ;
        }
        else
        {
            rindex = get_rindex(dir);
            printf("%d\n", rindex);
            prev = malloc(rindex + 1);
            ft_strncpy(prev, dir, rindex);
            prev[rindex] = '\0';
            printf("%s\n", prev);
        }
        status = chdir(prev);
        free(prev);
        free(dir);
    }
    else
        status = chdir(args[1]);
    if (status == -1)
        perror("chdir");
}*/

/*int main(int ac, char **av)
{
    ft_cd(av);
    
    // Afficher le répertoire courant pour vérifier
    char *cwd = getcwd(NULL, 0);
    printf("Répertoire actuel: %s\n", cwd);
    free(cwd);
    
    return 0;
}*/
