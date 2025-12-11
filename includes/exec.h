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

typedef struct s_command {
	char	*cmd_name;
	char	*cmd_path;
	char	**args;
	char	**tab_env;
	int		i;
	int		j;
	int		k;
	int		arg_count;
} t_command;

typedef struct s_handle {
	int			i;
	int			fd;
	char		*filename;
	t_ast_node	*redir;
} t_handle;

typedef struct s_heredoc {
	int	*heredoc_pipes;
	int	i;
	int	j;
	int	k;
	t_ast_node	*command;
	t_ast_node *redir_node;
} t_heredoc;

typedef struct s_has_heredoc {
	int i;
	int j;
	int k;
	t_ast_node *command;
	t_ast_node *redir_node;
} t_has_heredoc;

// execute_ast.c
int		is_builtins(char *cmd);
void    execute_builtins(char **args, t_env *env, int code);
void 	execute_command(t_global *global);
void	execute_pipeline(t_global *global);
void	execute_ast(t_global *global);

// execute_utils.c
int		launch_pipe(t_global *global, t_pipeline *data);
void	handle_redirections(t_ast_node *redirection_node);
void	exec_errors_specific(char **arg);
int		is_specific_cmd(char **arg);

//command.c
void	init_command(t_command *cmd);
void	execute_command_1(t_global *global, t_command *cmd);
void	execute_command_2(t_global *global, t_command *cmd);

// command_utils.c
char	*find_command_in_path(char *cmd, t_env *env);
int		run_cmd(t_global *global, t_command *cmd);

// heredocs.c
int 	handle_heredoc(char *delimiter);
void    prepare_all_heredocs_1(t_heredoc *hdc);
int		*prepare_all_heredocs(t_ast_node *pipeline);
int		has_heredocs(t_ast_node *pipeline);
void 	cleanup_heredoc_pipes(int *heredoc_pipes, int count);

// redirection.c
void    redirection_1(t_handle *data);
void    redirection_2(t_handle *data);
void    redirection_3(t_handle *data);

// process.c
void    child_process(t_global *global, t_pipeline *data);

// pipeline.c
void	execute_pipeline_1(t_global *global, t_pipeline *data);
void    execute_pipeline_2(t_global *global, t_pipeline *data);
int		execute_pipeline_3(t_global *global, t_pipeline *data);


#endif
