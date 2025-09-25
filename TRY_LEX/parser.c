/*
pipeline     -> command '|' pipeline
pipeline     -> command

command      -> word argument_list redirection_list
argument_list -> argument argument_list
argument_list -> ε (vide)

argument     -> word
argument     -> quoted_string

redirection_list -> redirection redirection_list  
redirection_list -> ε

redirection  -> '<' word
redirection  -> '>' word
redirection  -> '<<' word
redirection  -> '>>' word

quoted_string -> QUOTE content QUOTE
quoted_string -> DOUBLE_QUOTE content DOUBLE_QUOTE

word         -> WORD
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Vos structures existantes
typedef enum e_token
{
	WORD = 0,
	IO_LOCA,
	D_LESS,
	D_GREAT,
	LESS,
	GREAT,        // 5
	PIPE,         // 6
	QUOTE,        // 7
	DOUBLE_QUOTE, // 8
	EXPAND,       // 9 (votre DOLLAR devient EXPAND)
	ERROR
} t_token;

typedef struct s_lexem
{
	t_token token;
	char *input;
	struct s_lexem *next;
} t_lexem;

// Forward declaration
typedef struct s_ast_node t_ast_node;

// Structures spécialisées pour chaque type de nœud
typedef struct s_pipeline_data
{
	t_ast_node *left_cmd;     // Commande de gauche
	t_ast_node *right_pipeline; // Pipeline de droite
} t_pipeline_data;

typedef struct s_command_data
{
	t_ast_node *cmd_word;     // Le mot de la commande (ex: "ls")
	t_ast_node *arguments;    // Liste chaînée des arguments
	t_ast_node *redirections; // Liste chaînée des redirections
} t_command_data;

typedef struct s_word_data
{
	char *value;              // La valeur du mot
	int needs_expansion;      // 1 si le mot contient $, `, $(, $((, *, ?, [
	int quote_type;           // 0=none, 1=single, 2=double
} t_word_data;

typedef struct s_redirection_data
{
	t_token redir_type;       // LESS, GREAT, D_LESS, D_GREAT
	t_ast_node *target;       // Le fichier cible
} t_redirection_data;

typedef struct s_variable_data
{
	char *name;               // Nom de la variable (ex: "USER")
} t_variable_data;

typedef struct s_quoted_string_data
{
	t_token quote_type;       // QUOTE ou DOUBLE_QUOTE
	t_ast_node *content_list; // Liste chaînée du contenu (mots, variables, etc.)
	int needs_expansion;      // 1 si expansion nécessaire
} t_quoted_string_data;

// Types de nœuds AST
typedef enum e_node_type
{
	NODE_PIPELINE,
	NODE_COMMAND,
	NODE_WORD,
	NODE_REDIRECTION,
	NODE_QUOTED_STRING,
	NODE_VARIABLE    // Nouveau type pour $VAR
} t_node_type;

// Structure principale du nœud AST avec union
typedef struct s_ast_node
{
	t_node_type type;
	
	union {
		t_pipeline_data pipeline;
		t_command_data command;
		t_word_data word;
		t_redirection_data redirection;
		t_quoted_string_data quoted_string;
		t_variable_data variable;
	} data;
	
	struct s_ast_node *next;  // Pour chaîner les éléments de liste
} t_ast_node;

typedef struct s_parser
{
	t_lexem *current;
	int error;
} t_parser;

// Prototypes
t_ast_node *create_pipeline_node(t_ast_node *left, t_ast_node *right);
t_ast_node *create_command_node(t_ast_node *cmd_word, t_ast_node *args, t_ast_node *redirections);
t_ast_node *create_word_node(const char *value);
t_ast_node *create_redirection_node(t_token redir_type, t_ast_node *target);
t_ast_node *create_quoted_string_node(t_token quote_type, t_ast_node *content_list);
t_ast_node *create_variable_node(const char *name);

// Fonctions d'expansion
int check_expansion_in_quotes(t_ast_node *content_list, t_token quote_type);

t_ast_node *parse_pipeline(t_parser *parser);
t_ast_node *parse_command(t_parser *parser);
t_ast_node *parse_argument_list(t_parser *parser);
t_ast_node *parse_argument(t_parser *parser);
t_ast_node *parse_redirection_list(t_parser *parser);
t_ast_node *parse_redirection(t_parser *parser);
t_ast_node *parse_quoted_string(t_parser *parser);
t_ast_node *parse_quoted_content(t_parser *parser, t_token quote_type);
t_ast_node *parse_variable(t_parser *parser);
t_ast_node *parse_word(t_parser *parser);

void advance_token(t_parser *parser);
int match_token(t_parser *parser, t_token expected);
void free_ast(t_ast_node *node);
void print_ast(t_ast_node *node, int depth);
void print_pipeline(t_ast_node *node, int depth);
void print_command(t_ast_node *node, int depth);
void print_word(t_ast_node *node, int depth);
void print_redirection(t_ast_node *node, int depth);
void print_quoted_string(t_ast_node *node, int depth);
void print_variable(t_ast_node *node, int depth);
void print_indent(int depth);
void free_pipeline(t_ast_node *node);
void free_command(t_ast_node *node);
void free_word(t_ast_node *node);
void free_redirection(t_ast_node *node);
void free_quoted_string(t_ast_node *node);
void free_variable(t_ast_node *node);
*/
// Fonctions d'expansion
int check_expansion_in_quotes(t_ast_node *content_list, t_token quote_type)
{
	if (!content_list)
		return 0;
	
	// Dans les guillemets simples, aucune expansion
	if (quote_type == QUOTE)
		return 0;
	
	// Dans les guillemets doubles, chercher des variables
	if (quote_type == DOUBLE_QUOTE)
	{
		t_ast_node *current = content_list;
		while (current)
		{
			if (current->type == NODE_VARIABLE)
				return 1;
			current = current->next;
		}
	}
	
	return 0;
}

// Fonctions de création des nœuds spécialisées
t_ast_node *create_pipeline_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node *node = malloc(sizeof(t_ast_node));
	if (!node)
		return NULL;
	
	node->type = NODE_PIPELINE;
	node->data.pipeline.left_cmd = left;
	node->data.pipeline.right_pipeline = right;
	node->next = NULL;
	return node;
}

t_ast_node *create_command_node(t_ast_node *cmd_word, t_ast_node *args, t_ast_node *redirections)
{
	t_ast_node *node = malloc(sizeof(t_ast_node));
	if (!node)
		return NULL;
	
	node->type = NODE_COMMAND;
	node->data.command.cmd_word = cmd_word;
	node->data.command.arguments = args;
	node->data.command.redirections = redirections;
	node->next = NULL;
	return node;
}

t_ast_node *create_word_node(const char *value)
{
	t_ast_node *node = malloc(sizeof(t_ast_node));
	if (!node)
		return NULL;
	
	node->type = NODE_WORD;
	if (value)
		node->data.word.value = strdup(value);
	else
		node->data.word.value = NULL;
	
	// Les mots simples n'ont jamais besoin d'expansion
	// car le lexer a déjà séparé les variables ($) en tokens distincts
	node->data.word.needs_expansion = 0;
	node->data.word.quote_type = 0; // Pas de quotes pour un mot simple
	node->next = NULL;
	return node;
}

t_ast_node *create_redirection_node(t_token redir_type, t_ast_node *target)
{
	t_ast_node *node = malloc(sizeof(t_ast_node));
	if (!node)
		return NULL;
	
	node->type = NODE_REDIRECTION;
	node->data.redirection.redir_type = redir_type;
	node->data.redirection.target = target;
	node->next = NULL;
	return node;
}

t_ast_node *create_quoted_string_node(t_token quote_type, t_ast_node *content_list)
{
	t_ast_node *node = malloc(sizeof(t_ast_node));
	if (!node)
		return NULL;
	
	node->type = NODE_QUOTED_STRING;
	node->data.quoted_string.quote_type = quote_type;
	node->data.quoted_string.content_list = content_list;
	
	// Déterminer si l'expansion est nécessaire selon le type de quotes
	node->data.quoted_string.needs_expansion = check_expansion_in_quotes(content_list, quote_type);
	node->next = NULL;
	return node;
}

t_ast_node *create_variable_node(const char *name)
{
	t_ast_node *node = malloc(sizeof(t_ast_node));
	if (!node)
		return NULL;
	
	node->type = NODE_VARIABLE;
	if (name)
		node->data.variable.name = strdup(name);
	else
		node->data.variable.name = NULL;
	node->next = NULL;
	return node;
}

// Avancer au token suivant
void advance_token(t_parser *parser)
{
	if (parser->current)
		parser->current = parser->current->next;
}

// Vérifier si le token actuel correspond au token attendu
int match_token(t_parser *parser, t_token expected)
{
	return parser->current && parser->current->token == expected;
}

// Parseur pour pipeline -> command '|' pipeline | command
t_ast_node *parse_pipeline(t_parser *parser)
{
	t_ast_node *cmd = parse_command(parser);
	if (!cmd)
		return NULL;
	
	if (match_token(parser, PIPE))
	{
		advance_token(parser); // consommer '|'
		t_ast_node *right_pipeline = parse_pipeline(parser);
		
		if (!right_pipeline)
		{
			free_ast(cmd);
			return NULL;
		}
		
		return create_pipeline_node(cmd, right_pipeline);
	}
	
	return cmd; // Juste une commande
}

// Parseur pour command -> word argument_list redirection_list
t_ast_node *parse_command(t_parser *parser)
{
	t_ast_node *word = parse_word(parser);
	if (!word)
		return NULL;
	
	// Parseur argument_list
	t_ast_node *args = parse_argument_list(parser);
	
	// Parseur redirection_list
	t_ast_node *redirections = parse_redirection_list(parser);
	
	return create_command_node(word, args, redirections);
}

// Parseur pour argument_list -> argument argument_list | ε
t_ast_node *parse_argument_list(t_parser *parser)
{
	if (!parser->current)
		return NULL;
	if (match_token(parser, PIPE))
		return NULL;
	if (match_token(parser, LESS))
		return NULL;
	if (match_token(parser, GREAT))
		return NULL;
	if (match_token(parser, D_LESS))
		return NULL;
	if (match_token(parser, D_GREAT))
		return NULL;
	
	t_ast_node *arg = parse_argument(parser);
	if (!arg)
		return NULL;
	
	t_ast_node *rest = parse_argument_list(parser);
	arg->next = rest;
	
	return arg;
}

// Parseur pour argument -> word | quoted_string
t_ast_node *parse_argument(t_parser *parser)
{
	if (match_token(parser, WORD))
		return parse_word(parser);
	
	if (match_token(parser, QUOTE))
		return parse_quoted_string(parser);
	
	if (match_token(parser, DOUBLE_QUOTE))
		return parse_quoted_string(parser);
	
	if (match_token(parser, EXPAND))
		return parse_variable(parser);
	
	return NULL;
}

// Parseur pour redirection_list -> redirection redirection_list | ε
t_ast_node *parse_redirection_list(t_parser *parser)
{
	if (!parser->current)
		return NULL;
	if (!match_token(parser, LESS) && !match_token(parser, GREAT) && !match_token(parser, D_LESS) && !match_token(parser, D_GREAT))
		return NULL;
	
	t_ast_node *redir = parse_redirection(parser);
	if (!redir)
		return NULL;
	
	t_ast_node *rest = parse_redirection_list(parser);
	redir->next = rest;
	
	return redir;
}

// Parseur pour redirection -> '<' word | '>' word | '<<' word | '>>' word
t_ast_node *parse_redirection(t_parser *parser)
{
	t_token redir_type;
	
	if (match_token(parser, LESS))
	{
		redir_type = LESS;
		advance_token(parser);
	}
	else if (match_token(parser, GREAT))
	{
		redir_type = GREAT;
		advance_token(parser);
	}
	else if (match_token(parser, D_LESS))
	{
		redir_type = D_LESS;
		advance_token(parser);
	}
	else if (match_token(parser, D_GREAT))
	{
		redir_type = D_GREAT;
		advance_token(parser);
	}
	else
		return NULL;
	
	t_ast_node *target = parse_word(parser);
	if (!target)
		return NULL;
	
	return create_redirection_node(redir_type, target);
}

// Parseur pour quoted_string -> QUOTE quoted_content QUOTE | DOUBLE_QUOTE quoted_content DOUBLE_QUOTE
t_ast_node *parse_quoted_string(t_parser *parser)
{
	t_token quote_type = parser->current->token;
	advance_token(parser); // consommer la quote d'ouverture
	
	// Parser le contenu de la chaîne quotée
	t_ast_node *content_list = parse_quoted_content(parser, quote_type);
	
	// Consommer la quote fermante (le lexer garantit qu'elle existe)
	advance_token(parser);
	
	return create_quoted_string_node(quote_type, content_list);
}

// Parseur pour le contenu des chaînes quotées
t_ast_node *parse_quoted_content(t_parser *parser, t_token quote_type)
{
	t_ast_node *first = NULL;
	t_ast_node *current = NULL;
	
	// Continuer jusqu'à la quote fermante
	while (parser->current && !match_token(parser, quote_type))
	{
		t_ast_node *element = NULL;
		
		if (match_token(parser, WORD))
			element = parse_word(parser);
		else if (match_token(parser, EXPAND))
			element = parse_variable(parser);
		else
			advance_token(parser); // Ignorer les tokens non reconnus
		
		if (element)
		{
			if (!first)
				first = element;
			else
				current->next = element;
			current = element;
		}
	}
	
	return first;
}

// Parseur pour variable -> EXPAND WORD
t_ast_node *parse_variable(t_parser *parser)
{
	if (!match_token(parser, EXPAND))
		return NULL;
	
	advance_token(parser); // consommer 'EXPAND' (votre token 9)
	
	if (!match_token(parser, WORD))
		return NULL; // Erreur: nom de variable attendu
	
	char *var_name = parser->current->input;
	advance_token(parser);
	return create_variable_node(var_name);
}

// Parseur pour word -> WORD
t_ast_node *parse_word(t_parser *parser)
{
	if (!match_token(parser, WORD))
		return NULL;
	
	char *value = parser->current->input;
	advance_token(parser);
	return create_word_node(value);
}

// Fonction principale de parsing
t_ast_node *parse(t_lexem *tokens)
{
	t_parser parser;
	parser.current = tokens;
	parser.error = 0;
	
	return parse_pipeline(&parser);
}

// Fonctions de libération spécialisées
void free_pipeline(t_ast_node *node)
{
	free_ast(node->data.pipeline.left_cmd);
	free_ast(node->data.pipeline.right_pipeline);
}

void free_command(t_ast_node *node)
{
	free_ast(node->data.command.cmd_word);
	free_ast(node->data.command.arguments);
	free_ast(node->data.command.redirections);
}

void free_word(t_ast_node *node)
{
	free(node->data.word.value);
}

void free_redirection(t_ast_node *node)
{
	free_ast(node->data.redirection.target);
}

void free_quoted_string(t_ast_node *node)
{
	free_ast(node->data.quoted_string.content_list);
}

void free_variable(t_ast_node *node)
{
	free(node->data.variable.name);
}

// Libération mémoire AST
void free_ast(t_ast_node *node)
{
	if (!node)
		return;
	
	if (node->type == NODE_PIPELINE)
		free_pipeline(node);
	else if (node->type == NODE_COMMAND)
		free_command(node);
	else if (node->type == NODE_WORD)
		free_word(node);
	else if (node->type == NODE_REDIRECTION)
		free_redirection(node);
	else if (node->type == NODE_QUOTED_STRING)
		free_quoted_string(node);
	else if (node->type == NODE_VARIABLE)
		free_variable(node);
	
	free_ast(node->next);
	free(node);
}



// Fonctions utilitaires pour accéder aux données
const char *get_word_value(t_ast_node *node)
{
	if (!node)
		return NULL;
	if (node->type != NODE_WORD)
		return NULL;
	return node->data.word.value;
}

int word_needs_expansion(t_ast_node *node)
{
	if (!node)
		return 0;
	if (node->type != NODE_WORD)
		return 0;
	return node->data.word.needs_expansion;
}

int quoted_string_needs_expansion(t_ast_node *node)
{
	if (!node)
		return 0;
	if (node->type != NODE_QUOTED_STRING)
		return 0;
	return node->data.quoted_string.needs_expansion;
}

t_token get_redirection_type(t_ast_node *node)
{
	if (!node)
		return ERROR;
	if (node->type != NODE_REDIRECTION)
		return ERROR;
	return node->data.redirection.redir_type;
}

const char *get_quoted_string_content(t_ast_node *node)
{
	// Note: Cette fonction est maintenant obsolète car le contenu
	// est une liste de nœuds, pas une chaîne simple
	if (!node)
		return NULL;
	if (node->type != NODE_QUOTED_STRING)
		return NULL;
	return NULL; // Plus applicable avec la nouvelle structure
}

const char *get_variable_name(t_ast_node *node)
{
	if (!node)
		return NULL;
	if (node->type != NODE_VARIABLE)
		return NULL;
	return node->data.variable.name;
}

t_ast_node *get_quoted_content_list(t_ast_node *node)
{
	if (!node)
		return NULL;
	if (node->type != NODE_QUOTED_STRING)
		return NULL;
	return node->data.quoted_string.content_list;
}
