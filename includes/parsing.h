#ifndef PARSING_H
# define PARSING_H

# include "env.h"
typedef enum e_token
{
        WORD = 0,
        IO_LOCA, //1
        DELIMITER,
        D_LESS, //3
        D_GREAT,
        LESS, //5
        GREAT,
        PIPE, //7
        ERROR
}       t_token;

typedef struct s_index
{
        int     pipe;
        int     less;
        int     great;
        int     space;
}       t_index;

//NODE LINKLIST
typedef struct s_lexem
{
        t_token token;
        char    *input;
        struct  s_lexem *next;
}       t_lexem;
//CURSOR TOKEN
typedef struct s_cursor
{
        int     position;
        char    *input;
        t_token current;
        t_token previous;
}       t_cursor;

typedef enum e_node_type
{
        NODE_PIPELINE,
        NODE_COMMAND,
        NODE_ARGUMENT,
        NODE_REDIRECTION,
        NODE_WORD,
        NODE_HEREDOC
}       t_node_type;

// NODE AST
typedef struct s_ast_node
{
    t_node_type type;
    char *value;
    struct s_ast_node **children;
    int child_count;
    int child_capacity;
        size_t children_byte_size;
}       t_ast_node;

//CURSOR PARSER
typedef struct s_parser
{
    t_lexem *current;
    t_ast_node *root;
}       t_parser;

typedef struct s_indexx
{
        int     i;
        int     j;
        int     k;
}       t_indexx;


#endif
