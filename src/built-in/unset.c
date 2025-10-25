#include "../../includes/minishell.h"

int	ft_unset(char	**args, t_env *env)
{
	printf("ft_unset\n");
	if (!args || !env)
		return (1);
	if (find_var(args[1], env) == 0)
		delete_var(args[1], env);
	return (0);
}
