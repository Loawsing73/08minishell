#include "../../includes/minishell.h"

int	ft_pwd(t_env *env)
{
	char	*pwd;

	printf("ft_pwd\n");
	pwd = get_var("PWD", env);
	printf("%s\n", pwd);
	return (0);
}
