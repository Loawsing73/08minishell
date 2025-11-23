#include "../../includes/minishell.h"

void    execute_pipeline_1(t_global *global, t_pipeline *data)
{
    data->command = global.tree->children[0];
    data->cmd_name = NULL;
    data->i = 0;
    while (data->i < data->command->child_count)
    {
        if (data->command->children[data->i]->type == NODE_WORD)
        {
            data->cmd_name = data->command->children[data->i]->value;
            break ;
        }
        data->i++;
    }
    if (data->cmd_name && is_builtins(data->cmd_name))
        data->is_single_builtin = 1;
}

static void	execute_pipeline_2_1(t_pipeline *data)
{
	if (data->command->children[data->i]->type == NODE_WORD)
		data->cmd_name = data->command->children[data->i]->value;
	else if (data->command->children[data->i]->type == NODE_ARGUMENT)
		data->arg_count = data->command->children[data->i]->child_count;
}

static void	execute_pipeline_2_2(t_pipeline *data)
{
	data->k = 0;
	while (data->k < data->command->children[data->i]->child_count)
	{
		data->args[data->j++] = data->command->children[data->i]->children[data->k]->value;
		data->k++;
	}
}

void    execute_pipeline_2(t_global *global, t_pipeline *data)
{
    data->arg_count = 0;
    data->j = 1;
	data->command = global->tree->children[0];
	data->cmd_name = NULL;
	data->i = 0;
	while (data->i < data->command->child_count)
	{
		execute_pipeline_2_1(data);
		data->i++;
	}
	data->args = malloc(sizeof(char *) * (data->arg_count + 2));
	data->args[0] = data->cmd_name;
	data->j = 1;
	data->i = 0;
	while (data->i < data->command->child_count)
	{
		if (data->command->children[data->i]->type == NODE_ARGUMENT)
			execute_pipeline_2_2(data);
		data->i++;
	}
	data->args[data->j] = NULL;
	execute_builtins(data->args, global->env, is_builtins(data->cmd_name));
	free(data->args);
}

static int	launch_pipe(t_global *global, t_pipeline *data)
{
	if (pipe(data->curr_pipe) == -1)
	{
		perror("pipe");
		cleanup_heredoc_pipes(data->heredoc_pipes, global->tree->child_count);
		return (1);
	}
	return (0);
}

int    execute_pipeline_3(t_global *global, t_pipeline *data)
{
    while (data->i < global->tree->child_count)
	{
		data->command = global->tree->children[data->i];
		if (data->i < global->tree->child_count - 1)
			if (launch_pipe(global, data) == 1)
				return (1);
		data->pid = fork();
		if (data->pid == 0)
			child_process(global, data);
		if (prev_pipe[0] != -1)
		{
			close(prev_pipe[0]);
			if (prev_pipe[1] != -1)
        		close(prev_pipe[1]);
		}
		if (data->i < global->tree->child_count - 1)
		{
			close(curr_pipe[1]);
			prev_pipe[0] = curr_pipe[0];
			prev_pipe[1] = -1;
		}
		data.i++;
	}
    return (0);
}