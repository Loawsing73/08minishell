#ifndef BUILT_IN_H
# define BUILT_IN_H

#include "env.h"

void 	ft_echo(char **args);
int		ft_cd(char **args, t_env *env);
int		ft_export(char **args, t_env *env);
int	ft_pwd(t_env *env);
int	ft_unset(char	**args, t_env *env);

#endif
