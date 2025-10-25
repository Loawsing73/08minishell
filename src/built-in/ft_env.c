#include "../../includes/minishell.h"

int	ft_env(t_env *env)
{
	t_env	*tmp;
	
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
