#include "../../includes/minishell.h"

void    redirection_1(t_handle *data)
{
    data->filename = data->redir->children[0]->value;
	data->fd = open(data->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->fd == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(data->fd, STDOUT_FILENO);
	close(data->fd);
}

void    redirection_2(t_handle *data)
{
    data->filename = data->redir->children[0]->value;
	data->fd = open(data->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(data->fd, STDOUT_FILENO);
	close(data->fd);
}

void    redirection_3(t_handle *data)
{
    data->filename = data->redir->children[0]->value;
	data->fd = open(data->filename, O_RDONLY);
	if (data->fd == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(data->fd, STDIN_FILENO);
	close(data->fd);
}