#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>


# include "parsing.h"
# include "lib.h"
# include "built_in.h"
# include "exec.h"
# include "env.h"
# include "ft_free.h"

typedef struct s_global
{
    t_env    *env;
    char    *input;
    t_cursor *cursor;
    t_lexem     *head;
    t_ast_node  *tree;  
}   t_global;

//parser.c
t_ast_node	*create_node_ast(t_node_type type, char *value);
void		add_child(t_ast_node *parent, t_ast_node *child);
void		free_ast(t_ast_node *node);
int		is_redirection_token(t_token token);
int		is_argument_token(t_token token);
void		consum_token(t_parser *parser);
int		match_token(t_parser *parser, t_token expected);
t_ast_node	*parse_pipeline(t_parser *parser);
t_ast_node	*parse_command(t_parser *parser);
t_ast_node	*parse_argument_list(t_parser *parser);
t_ast_node	*parse_argument(t_parser *parser);
t_ast_node	*parse_redirection_list(t_parser *parser);
t_ast_node	*parse_redirection(t_parser *parser);
t_ast_node	*parse_word(t_parser *parser);
t_ast_node	*parse(t_global *global);

//rendering.c
void print_ast(t_ast_node *node, int indent);

//tokenization.c
int	is_pipe(t_global *global);
int	is_word(t_global *gl);
int	is_less(t_global *global);
int	is_great(t_global *global);
int	get_index(int position, char *s, char c);
int	get_space(int position, char *s);
t_token	get_token(char c);
void	switch_token(t_token token, t_global *global);
t_lexem	*create_node(t_lexem *head, t_token token, char *input);
t_lexem *parsing_input(t_global *global);
void	free_lexem_list(t_global *global);

//trim_expand.c
char	*concate_hell(char *expanded_input, t_global *global);

//valid.c
int	valid_input(char *input);

//execute_ast.c
void	execute_ast(t_global *global);

#endif
