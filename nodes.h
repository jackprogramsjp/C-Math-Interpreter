#ifndef NODES_H
#define NODES_H

typedef enum {
    PlusNode,
    MinusNode,
    EmptyNode,
    NumberNode,
    AddNode,
    SubtractNode,
    MultiplyNode,
    DivideNode,
    PowerNode
} NodeType;

typedef struct Node {
    NodeType node_type;
    double value;
    struct Node *node_a;
    struct Node *node_b;
} Node;

void print_node(Node *);
void free_node(Node *);
Node *node_init(NodeType, double, Node *, Node *);

#endif // NODES_H
