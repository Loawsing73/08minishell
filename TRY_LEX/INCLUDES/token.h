#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef	enum e_token
{
	WORD = 0,
	IO_LOCA,
	D_LESS,
	D_GREAT,
	LESS,
	GREAT,
	PIPE,
	ERROR
}	t_token;

typedef struct	s_lexem
{
	t_token	token;
	char	*input;
	struct s_lexem	*next;
}	t_lexem;
typedef	struct	s_cursor
{
	int	position;
	char	*input;
	t_token	current;
	t_token	previous;
//	t_token	ante;
}	t_cursor;

typedef enum e_node_type
{
    NODE_PIPELINE,
    NODE_COMMAND,
    NODE_ARGUMENT,
    NODE_REDIRECTION,
    NODE_WORD
} t_node_type;

// Structure pour les nœuds de l'AST
typedef struct s_ast_node
{
    t_node_type type;
    char *value;                    // Pour les nœuds terminaux (WORD, etc.)
    struct s_ast_node **children;   // Tableau dynamique d'enfants
    int child_count;
    int child_capacity;
} t_ast_node;

// Structure pour le parser
typedef struct s_parser
{
    t_lexem *current;
    t_ast_node *root;
} t_parser;

char	*ft_substr(char *s, int start, int len);
int	ft_strlen(char *s);
char	*ft_strdup(char *s1);
int	ft_strncmp(char *s1, char *s2, int n);
int	ft_isalnum(int c);
char	*ft_strchr(char *s, int c);
char	*ft_strtrim(char *s1, char *set);
void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *my_realloc(void *ptr, size_t new_size);

int	is_pipe(t_lexem **head, t_cursor *cursor);
int	is_word(t_lexem **head, t_cursor *cursor);
int	is_great(t_lexem **head, t_cursor *cursor);
int	is_less(t_lexem **head, t_cursor *cursor);
int	get_index(int position, char *s, char c);
int	valid_input(char *input);
t_token	get_token(char c);
void	switch_token(t_token token, t_cursor *cursor);
t_lexem	*create_node(t_lexem *head, t_token token, char *input);
t_lexem *parsing_input(t_cursor *cursor, char *input);
int	get_space(int position, char *s);
void free_lexem_list(t_lexem *head);
char    *concate_hell(char *s, char **env);
char *get_variable(char **env, char *s);
char *get_depend(char *s);

// Prototypes des fonctions
t_ast_node *create_node_ast(t_node_type type, char *value);
void add_child(t_ast_node *parent, t_ast_node *child);
void free_ast(t_ast_node *node);
void print_ast(t_ast_node *node, int indent);

// Fonctions du parser (descente récursive)
t_ast_node *parse_pipeline(t_parser *parser);
t_ast_node *parse_command(t_parser *parser);
t_ast_node *parse_argument_list(t_parser *parser);
t_ast_node *parse_argument(t_parser *parser);
t_ast_node *parse_redirection_list(t_parser *parser);
t_ast_node *parse_redirection(t_parser *parser);
t_ast_node *parse_word(t_parser *parser);
t_ast_node *parse(t_lexem *lexem);

// Utilitaires
int is_redirection_token(t_token token);
int is_argument_token(t_token token);
void advance_token(t_parser *parser);
int match_token(t_parser *parser, t_token expected);

#endif
