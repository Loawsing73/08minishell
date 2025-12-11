#include "../../includes/minishell.h"

void    init_command(t_command *cmd)
{
    cmd->cmd_name = NULL;
    cmd->cmd_path = NULL;
    cmd->args = NULL;
    cmd->tab_env = NULL;
    cmd->i = 0;
    cmd->j = 1;
    cmd->k = 0;
    cmd->arg_count = 0;
}

void    execute_command_1(t_global *global, t_command *cmd)
{
    while (cmd->i < global->tree->child_count)
    {
        if (global->tree->children[cmd->i]->type == NODE_WORD)
            cmd->cmd_name = global->tree->children[cmd->i]->value;
        else if (global->tree->children[cmd->i]->type == NODE_ARGUMENT)
            cmd->arg_count = global->tree->children[cmd->i]->child_count;
        //sinon quoi ?
        cmd->i++;
    }
    cmd->i = 0;
}

void    execute_command_2(t_global *global, t_command *cmd)
{
   	while (cmd->i < global->tree->child_count)
	{
		if (global->tree->children[cmd->i]->type == NODE_ARGUMENT)
		{
			while (cmd->k < global->tree->children[cmd->i]->child_count)
			{
				args[cmd->j] = global->tree->children[cmd->i]->children[cmd->k]->value;
				cmd->j++;
				cmd->k++;
			}
		}
		cmd->i++;
	}
    cmd->args[cmd->j] = NULL;
	cmd->i = 0;
    while (cmd->i < global->tree->child_count)
	{
    	if (global->tree->children[cmd->i]->type == NODE_REDIRECTION)
        	handle_redirections(global->tree->children[cmd->i]);
    	cmd->i++;
	}
}