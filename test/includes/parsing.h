#ifndef PARSING_H
# define PARSING_H

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
t_ast_node	*parse(t_lexem *lexem);

#endif
