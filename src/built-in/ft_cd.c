#include "../../includes/minishell.h"

void	ft_cd(char	**args, t_env *env)
{
	char	new_path[PATH_MAX];

	printf("ft_cd\n");
	if (!args[1])	
	{
		new_path = find_var("HOME", env);
		if (!new_path)
			return ;
		if (chdir(new_path) == 1)
			return ;
		return (free(new_path));
	}
}
