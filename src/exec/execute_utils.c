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

void    execute_pipeline_2(t_global *global, t_pipeline *data)
{
    data->arg_count = 0;
    data->j = 1;
	data->command = global->tree->children[0];
	data->cmd_name = NULL;
	data->i = 0;
	while (data->i < data->command->child_count)
	{
		if (data->command->children[data->i]->type == NODE_WORD)
			data->cmd_name = data.command->children[data->i]->value;
		else if (data->command->children[data->i]->type == NODE_ARGUMENT)
			data->arg_count = data->command->children[data.i]->child_count;
		data->i++;
	}
	data->args = malloc(sizeof(char *) * (data->arg_count + 2));
	data->args[0] = data->cmd_name;
	data->j = 1;
	data->i = 0;
	while (data->i < data->command->child_count)
	{
		if (data->command->children[data->i]->type == NODE_ARGUMENT)
		{
			data->k = 0;
			while (data->k < data->command->children[data->i]->child_count)
			{
				data.args[data->j++] = data.command->children[data->i]->children[data.k]->value;
				data->k++;
			}
		}
		data->i++;
	}
	data->args[data->j] = NULL;
	execute_builtins(data->args, global->env, is_builtins(data->cmd_name));
	free(data->args);
}