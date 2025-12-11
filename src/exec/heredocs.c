#include "../../includes/minishell.h"

int handle_heredoc(char *delimiter)
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

void    prepare_all_heredocs_1(t_heredoc *hdc)
{
    while (hdc->j < hdc->command->child_count)
	{
	    if (hdc->command->children[hdc->j]->type == NODE_REDIRECTION)
		{
			hdc->redir_node = hdc->command->children[hdc->j];
			hdc->k = 0;
			while (hdc->k < hdc->redir_node->child_count)
			{
				if (hdc->redir_node->children[hdc->k]->type == NODE_HEREDOC)
				{
					hdc->heredoc_pipes[hdc->i] = handle_heredoc(hdc->redir_node->children[hdc->k]->value);
					break ;
				}
				hdc->k++;
			}
		}
		hdc->j++;
	}
}

int *prepare_all_heredocs(t_ast_node *pipeline)
{
    t_heredoc   hdc;

	hdc.heredoc_pipes = malloc(sizeof(int) * pipeline->child_count);
	if (!hdc.heredoc_pipes)
		return (NULL);
	hdc.i = 0;
	while (hdc.i < pipeline->child_count)
	{
		hdc.heredoc_pipes[hdc.i] = -1;
		hdc.i++;
	}
	hdc.i = 0;
	while (hdc.i < pipeline->child_count)
	{
		hdc.command = pipeline->children[hdc.i];
		hdc.j = 0;
        prepare_all_heredocs_1(&hdc);
		hdc.i++;
	}
	return (hdc.heredoc_pipes);
}

int has_heredocs(t_ast_node *pipeline)
{
	t_has_heredoc data;

	data.i = 0;
	while (data.i < pipeline->child_count)
	{
		data.command = pipeline->children[i];
		data.j = 0;
		while (data.j < data.command->child_count)
		{
			if (data.command->children[j]->type == NODE_REDIRECTION)
			{
				data.redir_node = data.command->children[j];
				data.k = 0;
				while (data.k < data.redir_node->child_count)
				{
					if (data.redir_node->children[k]->type == NODE_HEREDOC)
						return (1);
					data.k++;
				}
			}
			data.j++;
		}
		data.i++;
	}
	return (0);
}

void cleanup_heredoc_pipes(int *heredoc_pipes, int count)
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
