#ifndef TREE_H
# define TREE_H	

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Types d'opérations strictement énumérés
typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_NUMBER
} operation_type_t;

// Types de tokens
typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_ERROR
} token_type_t;

// Structure d'un token
typedef struct {
    token_type_t type;
    int value;
} token_t;

// Nœud de l'arbre binaire d'expression
typedef struct expr_node {
    operation_type_t type;
    union {
        int number;
        struct {
            struct expr_node* left;
            struct expr_node* right;
        } operation;
    } data;
} expr_node_t;

// État du parseur
typedef struct {
    const char* input;
    size_t position;
    token_t current_token;
} parser_state_t;

// Prototypes des fonctions
expr_node_t* create_number_node(int value);
expr_node_t* create_operation_node(operation_type_t op, expr_node_t* left, expr_node_t* right);
void free_expr_tree(expr_node_t* node);
int evaluate_tree(expr_node_t* node);
void print_tree(expr_node_t* node, int depth);

token_t next_token(parser_state_t* state);
void advance_token(parser_state_t* state);
expr_node_t* parse_expression(parser_state_t* state);
expr_node_t* parse_term(parser_state_t* state);
expr_node_t* parse_factor(parser_state_t* state);
#endif
