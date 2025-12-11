#include "../../includes/minishell.h"

char	*find_command_in_path(char *cmd, t_env *env)
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

int run_cmd(t_global *global, t_command *cmd)
{
    cmd->cmd_path = find_command_in_path(cmd->cmd_name, global->env);
	cmd->tab_env = convert_env_to_tab(global->env);
	if (!cmd->tab_env)
		return (1);
	execve(cmd->cmd_path, cmd->args, cmd->tab_env);
	perror("execve");
	if (cmd->cmd_path != cmd->cmd_name)
		free(cmd->cmd_path);
    return (0);
}