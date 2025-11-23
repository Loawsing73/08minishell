#include "../../includes/minishell.h"

void    child_process(t_global *global, t_pipeline *data)
{
    if (data->heredoc_pipes[data->i] != -1)
    {
        dup2(data->heredoc_pipes[data->i], STDIN_FILENO);
        close(data->heredoc_pipes[data->i]);
        data->heredoc_pipes[data->i] = -1;
    }
    else if (data->prev_pipe[0] != -1)
    {
        dup2(data->prev_pipe[0], STDIN_FILENO);
        close(data->prev_pipe[0]);
        close(data->prev_pipe[1]);
    }
    if (data->i < global->tree->child_count - 1)
    {
        close(data->curr_pipe[0]);
        dup2(data->curr_pipe[0]);
        close(data->curr_pipe[1]);
    }
    cleanup_heredoc_pipes(data->heredoc_pipes, global->tree->child_count);
    if (data->command->type == NODE_PIPELINE)
        execute_pipeline(global);
    else if (data->command->type == NODE_COMMAND)
        execute_command(global);
    else
        exit(1);
    exit(0);
}