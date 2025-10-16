#include "../../includes/minishell.h"

void	free_tab(char **tab)
{
	int	x;

	x = 0;
	while (tab[x])
	{
		free(tab[x]);
		x++;
	}
	free(tab);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->name)
			free(env->name);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}
