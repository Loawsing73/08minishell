#include "../../includes/minishell.h"

void	ft_cd(char	**args, t_env *env)
{
    char    *new_path;
	char	*old_path;
	char	*current_path;
	char	buffer[PATH_MAX];

    printf("ft_cd\n");
	(void)old_path;
    if (!args[1])
    {
		current_path = getcwd(buffer, 1024);
        new_path = find_var("HOME", env);
        if (!new_path)
            return ; // Peut être afficher un msg ? et free old_path si il existe
		chdir(new_path);
    }
	return ;
}
