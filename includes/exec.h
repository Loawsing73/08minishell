#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

typedef struct s_pipeline {
	int			arg_count;
	int			is_single_builtin;
	int			prev_pipe[2];
	int			curr_pipe[2];
	int			*heredoc_pipes;
	int			i;
	int			j;
	int			k;
	char		*cmd_name;
	char		**args;
	pid_t		pid;
	t_ast_node	*command;
} t_pipeline;

void	execute_ast(t_global *global);
void	execute_pipeline_1(t_global *global, t_pipeline *data);
void    execute_pipeline_2(t_global *global, t_pipeline *data);
int		is_builtins(char *cmd);

#endif
