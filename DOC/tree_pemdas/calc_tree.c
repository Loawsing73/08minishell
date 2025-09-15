#include "tree.h"
// node - int
expr_node_t* create_number_node(int value) 
{
    expr_node_t* node = malloc(sizeof(expr_node_t));
    if (!node)
		return NULL;
    node->type = OP_NUMBER;
    node->data.number = value;
    return node;
}

// node - opera
expr_node_t* create_operation_node(operation_type_t op, expr_node_t* left, expr_node_t* right)
{
    expr_node_t* node = malloc(sizeof(expr_node_t));
    if (!node)
		return NULL;
    node->type = op;
    node->data.operation.left = left;
    node->data.operation.right = right;
    return node;
}

// free arbre - suffix travers
void free_expr_tree(expr_node_t* node)
{
    if (!node)
		return;
    if (node->type != OP_NUMBER) {
        free_expr_tree(node->data.operation.left);
        free_expr_tree(node->data.operation.right);
    }
    free(node);
}

// effectuer calcul
int evaluate_tree(expr_node_t* node)
{
    int right_val;
	if (!node)
		return 0;
    if (node->type == OP_NUMBER)
        return node->data.number;
    if (node->type == OP_ADD)
        return evaluate_tree(node->data.operation.left) + evaluate_tree(node->data.operation.right);
    if (node->type == OP_SUB)
        return evaluate_tree(node->data.operation.left) - evaluate_tree(node->data.operation.right);
    if (node->type == OP_MUL)
        return evaluate_tree(node->data.operation.left) * evaluate_tree(node->data.operation.right);
    if (node->type == OP_DIV)
	{
        right_val = evaluate_tree(node->data.operation.right);
        if (right_val == 0) 
		{
            printf("Erreur: Division par zéro\n");
            return 0;
        }
        return evaluate_tree(node->data.operation.left) / right_val;
    }
    return 0;
}

// analyse - tokens 
token_t next_token(parser_state_t* state)
{
    token_t token = {TOKEN_ERROR, 0.0};
	char current;
	int value;
    while (state->input[state->position] == ' ' || state->input[state->position] == '\t')
        state->position++;
    current = state->input[state->position];
    if (current == '\0')
	{
        token.type = TOKEN_EOF;
        return token;
    }
    if (isdigit(current))
	{
        value = 0;
        while (isdigit(state->input[state->position]))
		{
            value = value * 10 + (state->input[state->position] - '0');
            state->position++;
        }
        token.value = value;
        token.type = TOKEN_NUMBER;
        return token;
    }
    if (current == '+')
	{
        token.type = TOKEN_PLUS;
        state->position++;
    }
	else if (current == '-')
	{
        token.type = TOKEN_MINUS;
        state->position++;
    }
	else if (current == '*')
	{
        token.type = TOKEN_MULTIPLY;
        state->position++;
    }
	else if (current == '/')
	{
        token.type = TOKEN_DIVIDE;
        state->position++;
    }
	else if (current == '(')
	{
        token.type = TOKEN_LPAREN;
        state->position++;
    }
	else if (current == ')')
	{
        token.type = TOKEN_RPAREN;
        state->position++;
    }
	else
	{
        token.type = TOKEN_ERROR;
        state->position++;
    }
    return token;
}

// aller au token suivant
void advance_token(parser_state_t* state)
{
    state->current_token = next_token(state);
}

// excpression : priorite plus basse + et -
// E = T + E
// E = T - E
// E = T
expr_node_t* parse_expression(parser_state_t* state)
{
    expr_node_t* left = parse_term(state);
	expr_node_t* right;
	operation_type_t op;
    if (!left)
		return NULL;
    while (state->current_token.type == TOKEN_PLUS || state->current_token.type == TOKEN_MINUS)
	{
        op = (state->current_token.type == TOKEN_PLUS) ? OP_ADD : OP_SUB;
        advance_token(state);
      	right = parse_term(state);
        if (!right)
		{
            free_expr_tree(left);
            return NULL;
        } 
        left = create_operation_node(op, left, right);
        if (!left)
		{
            free_expr_tree(right);
            return NULL;
        }
    }
    return left;
}

// terme : priorite moyenne * et "/"
// T = F * T
// T = F / T
// T = F
expr_node_t* parse_term(parser_state_t* state)
{
    expr_node_t* left = parse_factor(state);
    expr_node_t* right;
	operation_type_t op;
	if (!left)
		return NULL;
    while (state->current_token.type == TOKEN_MULTIPLY || state->current_token.type == TOKEN_DIVIDE)
	{
        op = (state->current_token.type == TOKEN_MULTIPLY) ? OP_MUL : OP_DIV;
        advance_token(state);
        right = parse_factor(state);
        if (!right)
		{
            free_expr_tree(left);
            return NULL;
        }
        left = create_operation_node(op, left, right);
        if (!left)
		{
            free_expr_tree(right);
            return NULL;
        }
    }
    return left;
}

// facteur : priorité haute int et )(
// F = int
// F = (E)
// F = -F
expr_node_t* parse_factor(parser_state_t* state)
{
    token_t token = state->current_token;
	if (token.type == TOKEN_NUMBER)
	{
        advance_token(state);
        return create_number_node(token.value);
    }
    if (token.type == TOKEN_LPAREN)
	{
        advance_token(state);
        expr_node_t* node = parse_expression(state);
        if (state->current_token.type != TOKEN_RPAREN) 
		{
            printf("Erreur: ')' attendue\n");
            free_expr_tree(node);
		 	return NULL;
        } 
        advance_token(state);
        return node;
    }
    if (token.type == TOKEN_MINUS)
	{
        advance_token(state);
        expr_node_t* node = parse_factor(state);
        if (!node) 
			return NULL;
        // 0 - x car oppose
        expr_node_t* zero = create_number_node(0);
        return create_operation_node(OP_SUB, zero, node);
    }
    printf("Erreur de syntaxe: token inattendu\n");
    return NULL;
}

// Fonction principale de parsing
expr_node_t* parse(const char* input)
{
    parser_state_t state = {0};
    state.input = input;
    state.position = 0; 
    advance_token(&state);
    expr_node_t* result = parse_expression(&state);
    if (state.current_token.type != TOKEN_EOF)
	{
        printf("Erreur: caractères supplémentaires après l'expression\n");
        free_expr_tree(result);
        return NULL;
    }
    return result;
}
//char *fgets(char *s, int size, FILE *stream); -> read until size from stream and store in buffer
//size_t strcspn(const char *s, const char *reject); -> calcul len seulement pas reject
int main() 
{
    char input[256];
    printf("Calculatrice\n");
    printf("'quit' pour quitter\n\n");
    while (1)
	{
        printf(">> ");
        if (!fgets(input, sizeof(input), stdin))
            break;
        input[strcspn(input, "\n")] = 0;
        if (strcmp(input, "quit") == 0) 
            break;
        if (strlen(input) == 0)
            continue;
        expr_node_t* tree = parse(input);
		if (tree) 
		{
            printf("TREE:\n");
            print_tree(tree, 0);
            printf("Résultat: %d\n\n", evaluate_tree(tree));
            free_expr_tree(tree);
        } 
		else
            printf("Erreur de parsing\n\n");
    }
    printf("Bye!\n");
    return 0;
}
