#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "nodes.h"
#include "values.h"

typedef struct Interpreter {
    const char *error;
} Interpreter;

Number interpreter_visit(Interpreter *, Node *);
Number interpreter_visit_add_node(Interpreter *, Node *);
Number interpreter_visit_subtract_node(Interpreter *, Node *);
Number interpreter_visit_multiply_node(Interpreter *, Node *);
Number interpreter_visit_divide_node(Interpreter *, Node *);
Number interpreter_visit_power_node(Interpreter *, Node *);
Number interpreter_visit_plus_node(Interpreter *, Node *);
Number interpreter_visit_minus_node(Interpreter *, Node *);

#endif // INTERPRETER_H
