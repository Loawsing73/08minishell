#include "../../includes/minishell.h"

void    execute_pipeline_1(t_global *global, t_pipeline *data, int *i)
{
    data->command = global.tree->children[0];
    data->cmd_name = NULL;
    i = 0;
    while (i < data->command->child_count)
    {
        if (data->command->children[i]->type == NODE_WORD)
        {
            data->cmd_name = data->command->children[i]->value;
            break ;
        }
        i++;
    }
    if (data->cmd_name && is_builtins(data->cmd_name))
        data->is_single_builtin = 1;
}

void    execute_pipeline_2(t_global *global, t_pipeline *data, int i, int j, int k)
{
    data->arg_count = 0;
}