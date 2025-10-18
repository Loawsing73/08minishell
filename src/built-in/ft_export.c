#include "../../includes/minishell.h"

void	print_export(t_env *env)
{
	char	*name;
	char	*value;
	t_env *tmp;

	(void)value;
	(void)name;
	tmp = env;
	name = NULL;
	value = NULL;
	while (tmp)
	{
		name = tmp->name;
		value = tmp->value;
		if (tmp->value)
			printf("declare -x %s=%s\n", tmp->name, tmp->value);
		else
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
	return ;
}

int	ft_export(char **str, t_env *env)
{
	if (!str[1])
		print_export(env);
	printf("Dude\n");
	return (0);
}
