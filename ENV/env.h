/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameerbe <mameerbe@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:16:49 by mameerbe          #+#    #+#             */
/*   Updated: 2025/10/14 20:38:47 by mameerbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include <limits.h>
#include <stdlib.h>

typedef struct s_env{
	char	*name;
	char	*value;
	char	*next;
}	t_env;

t_env	*new_var(char *name, char *value);
void	create_env(char **env);

#endif
