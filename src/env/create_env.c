/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameerbe <mameerbe@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:05:21 by mameerbe          #+#    #+#             */
/*   Updated: 2025/10/14 20:56:09 by mameerbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

static t_env	*create_minimal_env()
{
	t_env	*env;
	char	cwd[PATH_MAX];

	env = new_var("PWD", getcwd(cwd, sizeof(cwd)));
	env->next = new_var("SHLVL", "1");
	env->next->next = new_var("_", "");
	return (env);
}

static t_env	*convert_env(char **env)
{
	int		x;
	char	**tab;
	t_env	*convert;
	t_env	*tmp;
	
	convert = NULL;
	x = 0;
	while (env[x])
	{
		tab = split_env(env[x], '=');
		if (!tab)
			return (NULL);
		if (!convert)
		{
			convert = new_var(tab[0], tab[1]);
			if (!convert)
				return (free_tab(tab), NULL);
			tmp = convert;
		}
		else
		{
			tmp->next = new_var(tab[0], tab[1]);
			if (!tmp->next)
				return (free_tab(tab), free_env(convert), NULL);
			tmp = tmp->next;
		}
		x++;
	}
	return (convert);
}

t_env	*create_env(char **env)
{
	t_env	*new_env;
	int	size_env;

	new_env = NULL;
	size_env = 0;
	while (env[size_env])
		size_env++;
	if (size_env == 0)
		new_env = create_minimal_env();
	else
	{
		new_env = convert_env(env);
		if (!new_env)
			return (NULL);
	}
	return (new_env);
}
