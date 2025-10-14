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

# include "env.h"

t_env	*new_var(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env *));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}
