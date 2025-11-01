#include "../../includes/minishell.h"


static void bubble_sort_env(t_env *env)
{
	t_env *tmp;
	size_t	len1;
	size_t	len2;
	int		cmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->next)
		{
			len1 = ft_strlen(tmp->name);
			len2 = ft_strlen(tmp->next->name);
			if (len1 >= len2)
				cmp = ft_strncmp(tmp->name, tmp->next->name, len1);
			else
				cmp = ft_strncmp(tmp->name, tmp->next->name, len2);
			if (cmp > 0)
			{
				swap_var(tmp, tmp->next);
				tmp = env;
			}
		}
		tmp = tmp->next;
	}
}


static void	print_export(t_env *env)
{
	t_env *tmp;

	tmp = env;
	bubble_sort_env(tmp);
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		else
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
}

static int	check_if_exist(char *name, t_env *env)
{
	(void)env;
	if (!name)
		return (2);
	if (find_var(name, env) == 0)
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
