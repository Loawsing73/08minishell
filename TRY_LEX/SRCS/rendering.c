#include "../INCLUDES/token.h"
void print_ast(t_ast_node *node, int indent)
{
    int i;
    const char *type_names[] = {
        "PIPELINE", "COMMAND", "ARGUMENT", "REDIRECTION", "WORD", "HEREDOC"
    };
    
    if (!node)
        return;
    
    i = 0;
    while (i < indent)
    {
        printf(" ");
        i++;
    }
    
    printf("%s", type_names[node->type]);
    if (node->value)
        printf(": \"%s\"", node->value);
    printf("\n");
    
    i = 0;
    while (i < node->child_count)
    {
        print_ast(node->children[i], indent + 1);
        i++;
    }
}