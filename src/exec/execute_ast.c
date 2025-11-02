#include "../../includes/minishell.h"

/*si input "." => msg d'erreur spécial dans bash*/
static void	exeute_errors_specific(char **arg)
{
	if (ft_strncmp(arg[0], ".", 2) == 0)
	{
		if (arg[1])
			printf("Command not found\n");
		else
			printf("Filename argument required\n");
		return ;
	}
	if (ft_strncmp(arg[0], "..", 2) == 0)
	{
		printf("Command not found\n");
		return ;
	}

}
/*bool : "." ou ".." seul*/
static int	is_specific_cmd(char **arg)
{
	if (ft_strncmp(arg[0], ".", 2) == 0 || ft_strncmp(arg[0], "..", 2) == 0)
		return (1);
	return (0);
}
/*bool : buitins => renvoie code pou savoir quel builtin*/
int is_builtins(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (2);
	if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (4);
	if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (3);
	if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (5);
	if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (6);
	if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		return (7);
	return (0);
}

/*execute le builtin en fonction du code renvoyé*/
void    execute_builtins(char **args, t_env *env, int code)
{
	if (code == 1)
		ft_echo(args);
    else if (code == 2)
        ft_cd(args, env);
	else if (code == 4)
		ft_export(args, env);
	else if (code == 3)
		ft_pwd(env);
	else if (code == 5)
		ft_unset(args, env);
	else if (code == 6)
		ft_env(env);
	else if (code == 7)
		ft_exit_bul(args, env);
} 
static int has_heredocs(t_ast_node *pipeline)
{
	int i, j, k;
	t_ast_node *command;
	t_ast_node *redir_node;

	i = 0;
	while (i < pipeline->child_count)
	{
		command = pipeline->children[i];
		j = 0;
		while (j < command->child_count)
		{
			if (command->children[j]->type == NODE_REDIRECTION)
			{
				redir_node = command->children[j];
				k = 0;
				while (k < redir_node->child_count)
				{
					if (redir_node->children[k]->type == NODE_HEREDOC)
						return (1);
					k++;
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

static void cleanup_heredoc_pipes(int *heredoc_pipes, int count)
{
	int i;

	i = 0;
	if (!heredoc_pipes)
		return ;
	while (i < count)
	{
		if (heredoc_pipes[i] != -1)
			close(heredoc_pipes[i]);
		i++;
	}
	free(heredoc_pipes);
}

static int handle_heredoc(char *delimiter)
{
	int     pipe_fd[2];
	char    *line;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		else if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

static int *prepare_all_heredocs(t_ast_node *pipeline)
{
	int *heredoc_pipes;
	int i, j, k;
	t_ast_node *command;
	t_ast_node *redir_node;

	heredoc_pipes = malloc(sizeof(int) * pipeline->child_count);
	if (!heredoc_pipes)
		return (NULL);
	i = 0;
	while (i < pipeline->child_count)
	{
		heredoc_pipes[i] = -1;
		i++;
	}
	i = 0;
	while (i < pipeline->child_count)
	{
		command = pipeline->children[i];
		j = 0;
		while (j < command->child_count)
		{
			if (command->children[j]->type == NODE_REDIRECTION)
			{
				redir_node = command->children[j];
				k = 0;
				while (k < redir_node->child_count)
				{
					if (redir_node->children[k]->type == NODE_HEREDOC)
					{
						heredoc_pipes[i] = handle_heredoc(redir_node->children[k]->value);
						break ;
					}
					k++;
				}
			}
			j++;
		}
		i++;
	}
	return (heredoc_pipes);
}
/*gère >>, > et <*/
static void handle_redirections(t_ast_node *redirection_node)
{
	int         i;
	int         fd;
	char        *filename;
	t_ast_node  *redir;

	i = 0;
	while (i < redirection_node->child_count)
	{
		redir = redirection_node->children[i];
		if (ft_strncmp(redir->value, ">>", 3) == 0)
		{
			filename = redir->children[0]->value;
			fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("open");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strncmp(redir->value, ">", 2) == 0)
		{
			filename = redir->children[0]->value;
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("open");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (ft_strncmp(redir->value, "<", 2) == 0)
		{
			filename = redir->children[0]->value;
			fd = open(filename, O_RDONLY);
			if (fd == -1)
			{
				perror("open");
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		i++;
	}
}

static char	*find_command_in_path(char *cmd, t_env *env)
{
	char	*value_path;
	char	*tmp;
	char	*full_path;
	char	**paths;
	int		x;

	x = 0;
	value_path = get_var("PATH", env);
	if (!value_path)
		return (NULL);
	paths = ft_split(value_path, ':');
	if (!paths)
		return (free(value_path), NULL);
	while (paths[x])
	{
		tmp = ft_strjoin(paths[x], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			free_tab(paths);
			return (full_path);
		}
		free(full_path);
		x++;
	}
	free_tab(paths);
	return (cmd);
}

static void execute_command(t_global *global)
/*si word = args[0]
si argument, remplit args[i]
puis regarde args[0], regarde si cas spécifique (.) 
puis regarde si c'est builtin*/
{
	char    *cmd_name;
	char    *cmd_path;
	char    **args;
	char	**tab_env;
	int     i;
	int     j;
	int     arg_count;
	
	cmd_name = NULL;
	cmd_path = NULL;
	args = NULL;
	arg_count = 0;
	i = 0;
	while (i < global->tree->child_count)
	{
		if (global->tree->children[i]->type == NODE_WORD)
			cmd_name = global->tree->children[i]->value;
		else if (global->tree->children[i]->type == NODE_ARGUMENT)
			arg_count = global->tree->children[i]->child_count;
		i++;
	}
	args = malloc(sizeof(char *) * (arg_count + 2));
	args[0] = cmd_name;
	j = 1;
	i = 0;
	while (i < global->tree->child_count)
	{
		if (global->tree->children[i]->type == NODE_ARGUMENT)
		{
			int k = 0;
			while (k < global->tree->children[i]->child_count)
			{
				args[j] = global->tree->children[i]->children[k]->value;
				j++;
				k++;
			}
		}
		i++;
	}
	args[j] = NULL;
	i = 0;
	while (i < global->tree->child_count)
	{
    	if (global->tree->children[i]->type == NODE_REDIRECTION)
        	handle_redirections(global->tree->children[i]);
    	i++;
	}
	if (is_specific_cmd(args))
		exeute_errors_specific(args);
	else if (is_builtins(cmd_name))
		execute_builtins(args, global->env, is_builtins(cmd_name));
	else
	{
		cmd_path = find_command_in_path(cmd_name, global->env);
		tab_env = convert_env_to_tab(global->env);
		if (!tab_env)
			return ;
		execve(cmd_path, args, tab_env);
		perror("execve");
		if (cmd_path != cmd_name)
			free(cmd_path);
	}
	free(args);
	exit(1);
}

static void execute_pipeline(t_global *global)
{
	t_pipeline	data;
	int			i;
	int			j;
	int			k;
	/*int			prev_pipe[2];
	int			curr_pipe[2];
	pid_t		pid;
	t_ast_node	*command;
	int			*heredoc_pipes;
	char		*cmd_name;
	int			is_single_builtin;
	char		**args;
	int			arg_count;*/

	data.is_single_builtin = 0;
	if (global->tree->child_count == 1)
	{
		data.command = global->tree->children[0];
		data.cmd_name = NULL;
		data.i = 0;
		while (data.i < data.command->child_count)
		{
			if (data.command->children[i]->type == NODE_WORD)
			{
				data.cmd_name = data.command->children[i]->value;
				break ;
			}
			data.i++;
		}
		if (data.cmd_name && is_builtins(data.cmd_name))
			data.is_single_builtin = 1;
	}
	if (data.is_single_builtin)
	{
		data.arg_count = 0;
		data.j = 1;
		data.command = global->tree->children[0];
		data.cmd_name = NULL;
		data.i = 0;
		while (data.i < data.command->child_count)
		{
			if (data.command->children[i]->type == NODE_WORD)
				data.cmd_name = data.command->children[i]->value;
			else if (data.command->children[i]->type == NODE_ARGUMENT)
				data.arg_count = data.command->children[i]->child_count;
			data.i++;
		}
		data.args = malloc(sizeof(char *) * (data.arg_count + 2));
		data.args[0] = data.cmd_name;
		data.j = 1;
		data.i = 0;
		while (data.i < data.command->child_count)
		{
			if (data.command->children[i]->type == NODE_ARGUMENT)
			{
				data.k = 0;
				while (data.k < data.command->children[i]->child_count)
				{
					data.args[data.j++] = data.command->children[data.i]->children[data.k]->value;
					data.k++;
				}
			}
			data.i++;
		}
		data.args[data.j] = NULL;
		execute_builtins(data.args, global->env, is_builtins(data.cmd_name));
		free(data.args);
		return ;
	}
	data.heredoc_pipes = prepare_all_heredocs(global->tree);
	if (!data.heredoc_pipes && has_heredocs(global->tree))
	{
		perror("heredoc preparation failed");
		return ;
	}
	data.prev_pipe[0] = -1;
	data.prev_pipe[1] = -1;
	data.i = 0;
	while (data.i < global->tree->child_count)
	{
		data.command = global->tree->children[i];
		if (data.i < global->tree->child_count - 1)
		{
			if (pipe(data.curr_pipe) == -1)
			{
				perror("pipe");
				cleanup_heredoc_pipes(data.heredoc_pipes, global->tree->child_count);
				return ;
			}
		}
		data.pid = fork();
		if (data.pid == 0)
		{
			if (data.heredoc_pipes[data.i] != -1)
			{
				dup2(data.heredoc_pipes[i], STDIN_FILENO);
				close(data.heredoc_pipes[i]);
				data.heredoc_pipes[i] = -1;
			}
			else if (prev_pipe[0] != -1)
			{
				dup2(prev_pipe[0], STDIN_FILENO);
				close(prev_pipe[0]);
				close(prev_pipe[1]);
			}
			if (i < global->tree->child_count - 1)
			{
				close(curr_pipe[0]);
				dup2(curr_pipe[1], STDOUT_FILENO);
				close(curr_pipe[1]);
			}
			cleanup_heredoc_pipes(heredoc_pipes, global->tree->child_count);
			if (command->type == NODE_PIPELINE)
        		execute_pipeline(command, global->env);  // Récursif
    		else if (command->type == NODE_COMMAND)
        		execute_command(command, global->env);
    		else
				exit(1);
			exit(0);
		}
		if (prev_pipe[0] != -1)
		{
			close(prev_pipe[0]);
			if (prev_pipe[1] != -1)
        		close(prev_pipe[1]);
		}
		if (i < global->tree->child_count - 1)
		{
			close(curr_pipe[1]);
			prev_pipe[0] = curr_pipe[0];
			prev_pipe[1] = -1;
		}
		i++;
	}
	cleanup_heredoc_pipes(heredoc_pipes, global->tree->child_count);
	i = 0;
	while (i < global->tree->child_count)
	{
		wait(NULL);
		i++;
	}
}

void execute_ast(t_global *global)
{
	if (!global->tree)
		return ;
	if (global->tree->type == NODE_PIPELINE)
		execute_pipeline(global);
	else if (node->type == NODE_COMMAND)
		execute_command(node, env);
}
