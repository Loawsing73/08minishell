#include "../INCLUDES/token.h"

// Création d'un nœud AST
t_ast_node *create_node_ast(t_node_type type, char *value)
{
	t_ast_node *node = malloc(sizeof(t_ast_node));

	if (!node)
		return (NULL);
	node->type = type;
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->children = NULL;
	node->child_count = 0;
	node->child_capacity = 0;
	return (node);
}

// ajouter node - exponentiel
void add_child(t_ast_node *parent, t_ast_node *child)
{
	if (!parent || !child)
		return;
	if (parent->child_count >= parent->child_capacity)
	{
		if (parent->child_capacity == 0)
			parent->child_capacity = 4;
		else
			parent->child_capacity = parent->child_capacity * 2;
		parent->children = my_realloc(parent->children, parent->child_capacity * sizeof(t_ast_node*));
	}
	parent->children[parent->child_count] = child;
	parent->child_count++;
}

// free ast
void free_ast(t_ast_node *node)
{
	int i;

	if (!node)
		return ;
	
	i = 0;
	while (i < node->child_count)
	{
		free_ast(node->children[i]);
		i++;
	}
	free(node->children);
	free(node->value);
	free(node);
}

int is_redirection_token(t_token token)
{
	if (token == LESS)
		return 1;
	if (token == GREAT)
		return 1;
	if (token == D_LESS)
		return 1;
	if (token == D_GREAT)
		return 1;
	return 0;
}

int is_argument_token(t_token token)
{
	if (token == WORD)
		return (1);
	return (0);
}

void advance_token(t_parser *parser)
{
	if (parser->current)
		parser->current = parser->current->next;
}

int match_token(t_parser *parser, t_token expected)
{
	if (!parser->current)
		return (0);
	if (parser->current->token == expected)
		return (1);
	return (0);
}

// pipeline -> command '|' pipeline
// pipeline -> command
t_ast_node *parse_pipeline(t_parser *parser)
{
	t_ast_node *pipeline;
	t_ast_node *command;

	pipeline = create_node_ast(NODE_PIPELINE, NULL);
	command = parse_command(parser);
	if (!command)
	{
		free_ast(pipeline);
		return (NULL);
	}
	add_child(pipeline, command);
	if (match_token(parser, PIPE))
	{
		advance_token(parser);
		t_ast_node *next_pipeline = parse_pipeline(parser);
		if (next_pipeline)
			add_child(pipeline, next_pipeline);
	}
	return (pipeline);
}

// command -> word argument_list redirection_list
t_ast_node *parse_command(t_parser *parser)
{
	t_ast_node *command;
	t_ast_node *word;
	t_ast_node *args;
	t_ast_node *redirections;

	if (!match_token(parser, WORD))
		return (NULL);
	command = create_node_ast(NODE_COMMAND, NULL);
	word = parse_word(parser);
	if (word)
		add_child(command, word);
	args = parse_argument_list(parser);
	if (args && args->child_count > 0)
		add_child(command, args);
	else if (args)
		free_ast(args);
	redirections = parse_redirection_list(parser);
	if (redirections && redirections->child_count > 0)
		add_child(command, redirections);
	else if (redirections)
		free_ast(redirections);
	return (command);
}

// argument_list -> argument argument_list
// argument_list -> ε
t_ast_node *parse_argument_list(t_parser *parser)
{
	t_ast_node *arg_list;
	t_token current_token;
	t_ast_node *arg;

	arg_list = create_node_ast(NODE_ARGUMENT, NULL);
	if (parser->current)
		current_token = parser->current->token;
	else
		current_token = ERROR;
	while (is_argument_token(current_token))
	{
		arg = parse_argument(parser);
		if (arg)
			add_child(arg_list, arg);
		else
			break;
		if (parser->current)
			current_token = parser->current->token;
		else
			current_token = ERROR;
	}
	return (arg_list);
}

// argument -> word
t_ast_node *parse_argument(t_parser *parser)
{
	if (match_token(parser, WORD))
		return parse_word(parser);
	return (NULL);
}

// redirection_list -> redirection redirection_list
// redirection_list -> ε
t_ast_node *parse_redirection_list(t_parser *parser)
{
	t_ast_node *redir_list;
	t_ast_node *redir;

	redir_list = create_node_ast(NODE_REDIRECTION, NULL);
	while (parser->current && is_redirection_token(parser->current->token))
	{
		redir = parse_redirection(parser);
		if (redir)
			add_child(redir_list, redir);
		else
			break;
	}
	return (redir_list);
}

// redirection -> '<' word | '>' word | '<<' word | '>>' word
t_ast_node *parse_redirection(t_parser *parser)
{
	char *redir_type;
	t_ast_node *redirection;
	t_ast_node *target;

	if (!parser->current || !is_redirection_token(parser->current->token))
		return (NULL);
	redir_type = NULL;
	if (parser->current->token == LESS)
		redir_type = "<";
	else if (parser->current->token == GREAT)
		redir_type = ">";
	else if (parser->current->token == D_LESS)
		redir_type = "<<";
	else if (parser->current->token == D_GREAT)
		redir_type = ">>";
	if (!redir_type)
		return (NULL);
	redirection = create_node_ast(NODE_REDIRECTION, redir_type);
	advance_token(parser);
	if (match_token(parser, IO_LOCA))
	{
		target =  create_node_ast(NODE_WORD, parser->current->input);
		advance_token(parser);
		if (target)
			add_child(redirection, target);
	}
	return (redirection);
}

// word -> WORD
t_ast_node *parse_word(t_parser *parser)
{
	t_ast_node *word;

	if (!match_token(parser, WORD))
		return (NULL);
	word = create_node_ast(NODE_WORD, parser->current->input);
	advance_token(parser);
	return (word);
}

// Fonction principale de parsing
t_ast_node *parse(t_lexem *lexem)
{
	t_parser parser;

	parser.current = lexem;
	parser.root = NULL;
	parser.root = parse_pipeline(&parser);
	return (parser.root);
}