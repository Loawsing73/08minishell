#include "../../includes/minishell.h"

void	ft_exit_bul(char **args, t_env *env)
{
	int		exit_code;
	char	*value_old_code;

	if (!args[1])
	{
		value_old_code = get_var("?", env);
		if (!value_old_code)
			exit(0);
		else
		{
			exit_code = ft_atoi(value_old_code);
			exit(exit_code);
		}
	}
	else
	{
		exit_code = ft_atoi(args[1]);
		if (exit_code < 0)
			exit_code = 256 + exit_code;
		exit(exit_code);
	}
}
