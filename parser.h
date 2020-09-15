#ifndef PARSER_H
#define PARSER_H

#include "tokens.h"
#include "nodes.h"

typedef struct Parser {
    Tokens *tokens;
    Token *current;
    char error[50];
    int index;
} Parser;

Node *parser_parse(Parser *parser, Tokens **tokens);
void parser_advance(Parser *parser);
Node *parser_expr(Parser *parser);
Node *parser_term(Parser *parser);
Node *parser_exponent(Parser *parser);
Node *parser_factor(Parser *parser);

#endif // PARSER_H
