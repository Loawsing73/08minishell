#include "../../includes/minishell.h"

//A revoir pour bien clean
int	ft_cd(char	**args, t_env *env)
{
    char    *new_path;
	char	*current_path;

    if (!args[1] || ft_strncmp(args[1], "~", ft_strlen(args[1])) == 0)
    {
		current_path = get_var("PWD", env);
        new_path = get_var("HOME", env);
        if (!new_path)
            return (1); // Peut être afficher un msg ? et free old_path si il existe
		update_var("OLDPWD", current_path, env);
		update_var("PWD", new_path, env);
		chdir(new_path);
    }
	else if (ft_strncmp(args[1], "-", ft_strlen(args[1])) == 0)
	{
		new_path = get_var("OLDPWD", env);
		if (!new_path)
			return (1);
		current_path = get_var("PWD", env);
		update_var("OLDPWD", current_path, env);
		update_var("PWD", new_path, env);
		if (chdir(new_path) == -1)
			return (1);
	}
	else
	{
		current_path = get_var("PWD", env);
		if (!current_path)
			return (1);
		update_var("OLDPWD", current_path, env);
		update_var("PWD", args[1], env);
		if (chdir(args[1]) == -1)
			return (1);
	}
	return (0);
}
