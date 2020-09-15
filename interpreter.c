#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "interpreter.h"
#include "nodes.h"
#include "values.h"

Number interpreter_visit(Interpreter *interpreter, Node *node) {
    interpreter->error = NULL;

    switch (node->node_type) {
        case NumberNode:
            return (Number) { node->value };
        case AddNode:
            return interpreter_visit_add_node(interpreter, node);
        case SubtractNode:
            return interpreter_visit_subtract_node(interpreter, node);
        case MultiplyNode:
            return interpreter_visit_multiply_node(interpreter, node);
        case DivideNode:
            return interpreter_visit_divide_node(interpreter, node);
        case PowerNode:
            return interpreter_visit_power_node(interpreter, node);
        case PlusNode:
            return interpreter_visit_plus_node(interpreter, node);
        case MinusNode:
            return interpreter_visit_minus_node(interpreter, node);
        default:
            interpreter->error = "Invalid node";
            return (Number) { 0 };
        }
}

Number interpreter_visit_add_node(Interpreter *interpreter, Node *node) {
    return (Number) { interpreter_visit(interpreter, node->node_a).value + interpreter_visit(interpreter, node->node_b).value };
}

Number interpreter_visit_subtract_node(Interpreter *interpreter, Node *node) {
    return (Number) { interpreter_visit(interpreter, node->node_a).value - interpreter_visit(interpreter, node->node_b).value };
}

Number interpreter_visit_multiply_node(Interpreter *interpreter, Node *node) {
    return (Number) { interpreter_visit(interpreter, node->node_a).value * interpreter_visit(interpreter, node->node_b).value };
}

Number interpreter_visit_divide_node(Interpreter *interpreter, Node *node) {
    double value = interpreter_visit(interpreter, node->node_b).value;

    if (value == 0.0) {
        interpreter->error = "Zero division error";
        return (Number) { 0 };
    }

    return (Number) { interpreter_visit(interpreter, node->node_a).value / value };
}

Number interpreter_visit_power_node(Interpreter *interpreter, Node *node) {
    return (Number) { pow(interpreter_visit(interpreter, node->node_a).value, interpreter_visit(interpreter, node->node_b).value) };
}

Number interpreter_visit_plus_node(Interpreter *interpreter, Node *node) {
    return interpreter_visit(interpreter, node->node_a);
}

Number interpreter_visit_minus_node(Interpreter *interpreter, Node *node) {
    return (Number) { -1 * interpreter_visit(interpreter, node->node_a).value };
}
