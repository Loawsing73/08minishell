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

# include "../PARSING/INCLUDES/token.h"
# include "env.h"

void	create_minimal_env()
{
	t_env	*env;
	char	cwd[PATH_MAX];

	env = new_var("PWD", getcwd(cwd, sizeof(cwd)));
	printf("NAME : %s | VALUE : %s\n", env->name, env->value);
	return ;
}

void	create_env(char **env)
{
	int	size_env;

	size_env = 0;
	while (env[size_env])
		size_env++;
	if (size_env == 0)
	{
		printf("here\n");
		create_minimal_env();
		return ;
	}
}
