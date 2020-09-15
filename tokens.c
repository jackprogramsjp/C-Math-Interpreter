#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"

const char *format_token_type(TokenType type) {
    switch (type) {
        case NUMBER: return "NUMBER";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case MULTIPLY: return "MULTIPLY";
        case DIVIDE: return "DIVIDE";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case POWER: return "POWER";
        case EOF_: return "EOF";
        default: return NULL;
    }
}

void print_token(Token *token) {
    if (token->type == NUMBER)
        printf("%s:%lf\n", format_token_type(token->type), token->value);
    else
        printf("%s\n", format_token_type(token->type));
}

void append_tokens(Tokens **tokens, Token token) {
    Tokens *new_token = malloc(sizeof(Tokens));
    Tokens *last = *tokens;

    new_token->token = token;
    new_token->next = NULL;

    if (*tokens == NULL) {
        *tokens = new_token;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_token;
}

Token *index_tokens(Tokens **tokens, int index) {
    if (*tokens == NULL)
        return NULL;

    Tokens *temp = *tokens;

    if (index == 0) {
        return &temp->token;
    }

    for (int i = 0; temp != NULL && i < index - 1; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL)
        return NULL;

    return &temp->next->token;
}

void print_tokens(Tokens *tokens) {
    while (tokens != NULL) {
        print_token(&tokens->token);
        tokens = tokens->next;
    }
}

void free_tokens(Tokens *tokens) {
    if (tokens->next != NULL) {
        free_tokens(tokens->next);
        tokens->next = NULL;
    }
    free(tokens);
}
