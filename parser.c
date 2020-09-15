#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "tokens.h"
#include "nodes.h"

Node *parser_parse(Parser *parser, Tokens **tokens) {
    parser->tokens = *tokens;
    append_tokens(&parser->tokens, (Token) { EOF_, 0 } );
    parser->index = 0;
    parser_advance(parser);

    memset(parser->error, 0, sizeof(parser->error));

    if (parser->current->type == EOF_)
        return node_init(EmptyNode, 0, NULL, NULL);

    Node *result = parser_expr(parser);

    if (parser->tokens == NULL)
        return NULL;

    if (result == NULL) {
        if (parser->tokens != NULL) {
            free_tokens(parser->tokens);
            parser->tokens = NULL;
        }

        return NULL;
    }

    if (parser->current->type != EOF_) {
        if (parser->tokens != NULL) {
            free_tokens(parser->tokens);
            parser->tokens = NULL;
        }
        snprintf(parser->error, sizeof(parser->error), "Invalid syntax");
        return NULL;
    }

    return result;
}

void parser_advance(Parser *parser) {
    parser->current = index_tokens(&parser->tokens, parser->index++);
}

Node *parser_expr(Parser *parser) {
    Node *result = parser_term(parser);

    if (parser->tokens == NULL)
        return NULL;

    while (parser->current->type != EOF_ && (parser->current->type == PLUS || parser->current->type == MINUS)) {
        if (parser->current->type == PLUS) {
            parser_advance(parser);
            if (result == NULL) {
                return result;
            }
            result = node_init(AddNode, 0, result, parser_term(parser));
        } else if (parser->current->type == MINUS) {
            parser_advance(parser);
            if (result == NULL) {
                return result;
            }
            result = node_init(SubtractNode, 0, result, parser_term(parser));
        }
    }

    return result;
}

Node *parser_term(Parser *parser) {
    Node *result = parser_exponent(parser);

    if (parser->tokens == NULL)
        return NULL;

    while (parser->current->type != EOF_ && (parser->current->type == MULTIPLY || parser->current->type == DIVIDE)) {
        if (parser->current->type == MULTIPLY) {
            parser_advance(parser);
            if (result == NULL) {
                return result;
            }
            result = node_init(MultiplyNode, 0, result, parser_exponent(parser));
        } else if (parser->current->type == DIVIDE) {
            parser_advance(parser);
            if (result == NULL) {
                return result;
            }
            result = node_init(DivideNode, 0, result, parser_exponent(parser));
        }
    }

    return result;
}

Node *parser_exponent(Parser *parser) {
    Node *result = parser_factor(parser);

    if (parser->tokens == NULL)
        return NULL;

    while (parser->current->type != EOF_ && (parser->current->type == POWER)) {
        if (parser->current->type == POWER) {
            parser_advance(parser);
            if (result == NULL) {
                return result;
            }
            result = node_init(PowerNode, 0, result, parser_factor(parser));
        }
    }

    return result;
}

Node *parser_factor(Parser *parser) {
    Token current = *parser->current;

    if (parser->tokens == NULL)
        return NULL;

    if (current.type == LPAREN) {
        parser_advance(parser);
        Node *result = parser_expr(parser);

        if (parser->current->type != RPAREN) {
            if (parser->tokens != NULL) {
                free_tokens(parser->tokens);
                parser->tokens = NULL;
            }

            if (result != NULL) {
                free_node(result);
                result = NULL;
            }

            snprintf(parser->error, sizeof(parser->error), "Syntax error");
        }

        parser_advance(parser);
        return result;
    } else if (current.type == NUMBER) {
        parser_advance(parser);
        return node_init(NumberNode, current.value, NULL, NULL);
    } else if (current.type == PLUS) {
        parser_advance(parser);
        return node_init(PlusNode, 0, parser_factor(parser), NULL);
    } else if (current.type == MINUS) {
        parser_advance(parser);
        return node_init(MinusNode, 0, parser_factor(parser), NULL);
    }

    if (parser->tokens != NULL) {
        free_tokens(parser->tokens);
        parser->tokens = NULL;
    }

    snprintf(parser->error, sizeof(parser->error), "Syntax error");

    return NULL;
}
