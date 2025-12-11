#include "../../includes/minishell.h"

int	launch_pipe(t_global *global, t_pipeline *data)
{
	if (pipe(data->curr_pipe) == -1)
	{
		perror("pipe");
		cleanup_heredoc_pipes(data->heredoc_pipes, global->tree->child_count);
		return (1);
	}
	return (0);
}

/*gère >>, > et <*/
void handle_redirections(t_ast_node *redirection_node)
{
	t_handle data;

	data.i = 0;
	while (data.i < redirection_node->child_count)
	{
		data.redir = redirection_node->children[data.i];
		if (ft_strncmp(data.redir->value, ">>", 3) == 0)
			redirection_1(&data);
		else if (ft_strncmp(data.redir->value, ">", 2) == 0)
			redirection_2(&data);
		else if (ft_strncmp(data.redir->value, "<", 2) == 0)
			redirection_3(&data);
		data.i++;
	}
}

/*si input "." => msg d'erreur spécial dans bash*/
void	exec_errors_specific(char **arg)
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
int	is_specific_cmd(char **arg)
{
	if (ft_strncmp(arg[0], ".", 2) == 0 || ft_strncmp(arg[0], "..", 2) == 0)
		return (1);
	return (0);
}