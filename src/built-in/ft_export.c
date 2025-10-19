#include "../../includes/minishell.h"

static void	print_export(t_env *env)
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
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		else
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
	return ;
}

static int	check_if_exist(char *name, t_env *env)
{
	(void)env;
	if (!name)
		return (2);
	if (!find_var(name, env) == 0)
		return (1);
	return (0);
}

static int	edit_or_add(char *arg, t_env *env)
{
	t_env	*tmp;
	char	**content;
	int		exist;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	content = split_env(arg, '=');
	exist = check_if_exist(content[0], env);
	if (exist == 1)
		tmp->next = new_var(content[0], content[1]);
	else if (exist == 0)
		update_var(content[0], content[1], env);
	else 
		return (1);
	return (0);
}

int	ft_export(char **args, t_env *env)
{
	if (!args[1])
		print_export(env);
	else
		edit_or_add(args[1], env);
	return (0);
}
