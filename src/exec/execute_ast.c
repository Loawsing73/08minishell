#include "../../includes/minishell.h"

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

void execute_command(t_global *global)
/*si word = args[0]
si argument, remplit args[i]
puis regarde args[0], regarde si cas spécifique (.) 
puis regarde si c'est builtin*/
{
	t_command	cmd;
	
	init_command(&cmd);
	execute_command_1(global, cmd);
	cmd.args = malloc(sizeof(char *) * (cmd.arg_count + 2));
	//gerer si le malloc rate
	cmd.args[0] = cmd.cmd_name;
	execute_command_2(global, &cmd);
	if (is_specific_cmd(cmd.args))
		exeute_errors_specific(cmd.args);
	else if (is_builtins(cmd.cmd_name))
		execute_builtins(cmd.args, global->env, is_builtins(cmd.cmd_name));
	else
	{
		if (run_cmd(global, &cmd) == 1)
			return ;
	}
	free(cmd.args);
	exit(1);
}

void execute_pipeline(t_global *global)
{
	t_pipeline	data;

	data.is_single_builtin = 0;
	if (global->tree->child_count == 1)
		execute_pipeline_1(global, &data);
	if (data.is_single_builtin)
		return (execute_pipeline_2(global, &data));
	data.heredoc_pipes = prepare_all_heredocs(global->tree);
	if (!data.heredoc_pipes && has_heredocs(global->tree))
		return (perror("heredoc preparation failed"));
	data.prev_pipe[0] = -1;
	data.prev_pipe[1] = -1;
	data.i = 0;
	if (execute_pipeline_3(global, &data) == 1)
		return ;
	cleanup_heredoc_pipes(heredoc_pipes, global->tree->child_count);
	data.i = 0;
	while (data.i < global->tree->child_count)
	{
		wait(NULL);
		data.i++;
	}
}

void execute_ast(t_global *global)
{
	if (!global->tree)
		return ;
	if (global->tree->type == NODE_PIPELINE)
		execute_pipeline(global);
	else if (global->tree->type == NODE_COMMAND)
		execute_command(global);
}
