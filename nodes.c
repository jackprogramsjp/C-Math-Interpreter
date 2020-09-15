#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"
#include "lexer.h"
#include "nodes.h"

void print_node(Node *node) {
    switch (node->node_type) {
        case NumberNode:
            printf("%lf", node->value);
            break;
        case PlusNode:
            if (node->node_a != NULL) {
                printf("(+");
                print_node(node->node_a);
                putchar(')');
            }
            break;
        case MinusNode:
            if (node->node_a != NULL) {
                printf("(-");
                print_node(node->node_a);
                putchar(')');
            }
            break;
        case AddNode:
            if (node->node_a != NULL && node->node_b != NULL) {
                putchar('(');
                print_node(node->node_a);
                printf(" + ");
                print_node(node->node_b);
                putchar(')');
            }
            break;
        case SubtractNode:
            if (node->node_a != NULL && node->node_b != NULL) {
                putchar('(');
                print_node(node->node_a);
                printf(" - ");
                print_node(node->node_b);
                putchar(')');
            }
            break;
        case MultiplyNode:
            if (node->node_a != NULL && node->node_b != NULL) {
                putchar('(');
                print_node(node->node_a);
                printf(" * ");
                print_node(node->node_b);
                putchar(')');
            }
            break;
        case DivideNode:
            if (node->node_a != NULL && node->node_b != NULL) {
                putchar('(');
                print_node(node->node_a);
                printf(" / ");
                print_node(node->node_b);
                putchar(')');
            }
            break;
        case PowerNode:
            if (node->node_a != NULL && node->node_b != NULL) {
                putchar('(');
                print_node(node->node_a);
                printf(" ** ");
                print_node(node->node_b);
                putchar(')');
            }
            break;
        default:
            printf("()");
    }
}

void free_node(Node *node) {
    if (node->node_a != NULL) {
        free_node(node->node_a);
        node->node_a = NULL;
    }

    if (node->node_b != NULL) {
        free_node(node->node_b);
        node->node_b = NULL;
    }

    free(node);
}

Node *node_init(NodeType node_type, double value, Node *node_a, Node *node_b) {
    Node *node = malloc(sizeof(Node));
    node->node_type = node_type;
    node->value = value;
    node->node_a = node_a;
    node->node_b = node_b;
    return node;
}
