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
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

//env_utils.c
t_env	*new_var(char *name, char *value);
void	print_env(t_env *env);
char	*get_var(char *name, t_env *env);
int		get_size_env(t_env *env);
char	**convert_env_to_tab(t_env *env);
void	update_var(char *name, char *new_content, t_env *env);
void	print_var(char *name, t_env *env);
int	find_var(char *name, t_env *env);
int	delete_var(char *name, t_env *env);

//create_env.c
t_env	*create_env(char **env);

#endif
