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

char	*find_var(char *name, t_env *env)
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
	return (tmp->value);
}
