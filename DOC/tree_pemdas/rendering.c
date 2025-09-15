#include "tree.h"

// utils rendering
void print_node_inline(expr_node_t* node, int depth)
{
    if (!node)
		return;
    int i = 0;
    while (i < depth)
	{
        printf("    ");
        i++;
    }
    if (node->type == OP_NUMBER)
        printf("%d", node->data.number);
    else if (node->type == OP_ADD)
        printf("+");
    else if (node->type == OP_SUB)
        printf("-");
    else if (node->type == OP_MUL)
        printf("*");
    else if (node->type == OP_DIV)
        printf("/");
}

// rendering tree (approx)
void print_tree(expr_node_t* node, int depth)
{
    if (!node) 
		return;
    int i = 0;
    while (i < depth) 
	{
        printf("    ");
        i++;
    }
    if (node->type == OP_NUMBER)
	{
        printf("%d\n", node->data.number);
        return;
    }
    if (node->type == OP_ADD)
	{
        printf("+\n");
        i = 0;
        while (i < depth)
		{
            printf("    ");
            i++;
        }
        printf("/ \\\n");
        
        // Si les deux enfants sont des nombres, les afficher sur la même ligne
        if (node->data.operation.left->type == OP_NUMBER && 
            node->data.operation.right->type == OP_NUMBER) {
            print_node_inline(node->data.operation.left, depth);
            printf("   ");
            print_node_inline(node->data.operation.right, 0);
            printf("\n");
        } else {
            // Enfant gauche aligné sous 
            print_tree(node->data.operation.left, depth);
            
            // Enfant droit aligné sous 
            i = 0;
            while (i < depth) {
                printf("    ");
                i++;
            }
            printf("  ");
            print_tree(node->data.operation.right, depth + 1);
        }
        return;
    }
    
    if (node->type == OP_SUB) {
        printf("-\n");
        i = 0;
        while (i < depth) {
            printf("    ");
            i++;
        }
        printf("/ \\\n");
        
        // Si les deux enfants sont des nombres, les afficher sur la même ligne
        if (node->data.operation.left->type == OP_NUMBER && 
            node->data.operation.right->type == OP_NUMBER) {
            print_node_inline(node->data.operation.left, depth);
            printf("   ");
            print_node_inline(node->data.operation.right, 0);
            printf("\n");
        } else {
            // Enfant gauche aligné sous /
            print_tree(node->data.operation.left, depth);
            
            // Enfant droit aligné sous 
            i = 0;
            while (i < depth) {
                printf("    ");
                i++;
            }
            printf("  ");
            print_tree(node->data.operation.right, depth + 1);
        }
        return;
    }
    
    if (node->type == OP_MUL) {
        printf("*\n");
        i = 0;
        while (i < depth) {
            printf("    ");
            i++;
        }
        printf("/ \\\n");
        
        // Si les deux enfants sont des nombres, les afficher sur la même ligne
        if (node->data.operation.left->type == OP_NUMBER && 
            node->data.operation.right->type == OP_NUMBER) {
            print_node_inline(node->data.operation.left, depth);
            printf("   ");
            print_node_inline(node->data.operation.right, 0);
            printf("\n");
        } else {
            // Enfant gauche aligné sous /
            print_tree(node->data.operation.left, depth);
            
            // Enfant droit aligné sous
            i = 0;
            while (i < depth) {
                printf("    ");
                i++;
            }
            printf("  ");
            print_tree(node->data.operation.right, depth + 1);
        }
        return;
    }
    
    if (node->type == OP_DIV) {
        printf("/\n");
        i = 0;
        while (i < depth) {
            printf("    ");
            i++;
        }
        printf("/ \\\n");
        
        // Si les deux enfants sont des nombres, les afficher sur la même ligne
        if (node->data.operation.left->type == OP_NUMBER && 
            node->data.operation.right->type == OP_NUMBER) {
            print_node_inline(node->data.operation.left, depth);
            printf("   ");
            print_node_inline(node->data.operation.right, 0);
            printf("\n");
        } else {
            // Enfant gauche aligné sous /
            print_tree(node->data.operation.left, depth);
            
            // Enfant droit aligné sous
            i = 0;
            while (i < depth) {
                printf("    ");
                i++;
            }
            printf("  ");
            print_tree(node->data.operation.right, depth + 1);
        }
        return;
    }
}
