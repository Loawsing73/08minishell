#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

typedef struct s_pipeline {
	int			arg_count;
	int			is_single_builtin;
	int			prev_pipe[2];
	int			curr_pipe[2];
	int			*heredoc_pipes;
	char		*cmd_name;
	char		**args;
	pid_t		pid;
	t_ast_node	*command;
} t_pipeline;

void	execute_ast(t_global *global);

#endif
