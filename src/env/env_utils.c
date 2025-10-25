/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameerbe <mameerbe@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:43:08 by mameerbe          #+#    #+#             */
/*   Updated: 2025/10/14 19:45:53 by mameerbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

t_env	*new_var(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	print_env(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		printf("Name -> %s | Value %s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

char	*get_var(char *name, t_env *env)
{
	t_env	*tmp;

	if (!name || !env)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(name, tmp->name, ft_strlen(name)) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	return (tmp->value);
}

int	get_size_env(t_env *env)
{
	t_env *tmp;
	int	count;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**convert_env_to_tab(t_env *env)
{
	t_env	*tmp;
	char	**tab_env;
	char	*join;
	int		size_env;
	int		x;

	tab_env = NULL;
	size_env = get_size_env(env);
	tab_env = malloc(sizeof(char *) * (size_env + 1));
	if (!tab_env)
		return (NULL);
	tmp = env;
	x = 0;
	while (tmp)
	{
		join = ft_strjoin(tmp->name, "=");
		tab_env[x] = ft_strjoin(join, tmp->value);
		x++;
		tmp = tmp->next;
	}
	return (tab_env);
}

void	update_var(char *name, char *new_content, t_env *env)
{
	t_env	*tmp;

	if (!new_content)
		return ;
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(name, tmp->name, ft_strlen(name)) == 0)
			break ;
		tmp = tmp->next;
	}
	tmp->value = new_content;
}

void	print_var(char *name, t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(name, tmp->name, ft_strlen(name)) == 0)
			break ;
		tmp = tmp->next;
	}
	printf("NAME %s | Value %s\n", tmp->name, tmp->value);
}

int	find_var(char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!name)
		return (1);
	while (tmp)
	{
		if (ft_strncmp(name, tmp->name, ft_strlen(name)) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int delete_var(char *name, t_env *env)
{
	t_env *tmp;
	t_env *last;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(name, tmp->name, ft_strlen(name)) == 0)
		{
			last->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return (0);
		}
		last = tmp;
		tmp = tmp->next;
	}
	return (1);
}

