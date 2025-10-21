#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

void	execute_ast(t_ast_node *node, t_env *new_env);

#endif
