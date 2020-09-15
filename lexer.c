#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokens.h"
#include "lexer.h"

Tokens *lexer_get_tokens(Lexer *lexer, const char *text, int text_size) {
    lexer->text = text; // If fgets, newline could be added to the end, but we are able to advance and ignore that
    lexer->text_size = text_size;
    lexer->index = 0;
    lexer_advance(lexer);

    memset(lexer->error, 0, sizeof(lexer->error));

    Tokens *tokens = NULL;

    while (lexer->current) {
        if (strchr(WHITESPACE, lexer->current) != NULL) {
            lexer_advance(lexer);
        } else if (lexer->current == '.' || strchr(DIGITS, lexer->current) != NULL) {
            append_tokens(&tokens, *lexer_get_number(lexer));
        } else if (lexer->current == '+') {
            lexer_advance(lexer);
            append_tokens(&tokens, (Token) { PLUS, 0 });
        } else if (lexer->current == '-') {
            lexer_advance(lexer);
            append_tokens(&tokens, (Token) { MINUS, 0 });
        } else if (lexer->current == '*') {
            lexer_advance(lexer);
            if (lexer->current == '*') {
                lexer_advance(lexer);
                append_tokens(&tokens, (Token) { POWER, 0 });
            } else
                append_tokens(&tokens, (Token) { MULTIPLY, 0 });
        } else if (lexer->current == '/') {
            lexer_advance(lexer);
            append_tokens(&tokens, (Token) { DIVIDE, 0 });
        } else if (lexer->current == '(') {
            lexer_advance(lexer);
            append_tokens(&tokens, (Token) { LPAREN, 0 });
        } else if (lexer->current == ')') {
            lexer_advance(lexer);
            append_tokens(&tokens, (Token) { RPAREN, 0 });
        } else {
            if (tokens != NULL) {
                free_tokens(tokens);
                tokens = NULL;
            }
            snprintf(lexer->error, sizeof(lexer->error), "Illegal character '%c'", lexer->current);
            return tokens;
        }
    }

    return tokens;
}

Token *lexer_get_number(Lexer *lexer) {
    int decimal_point_count = 0;
    int index = 0;
    char number_str[lexer->text_size];
    memset(number_str, 0, sizeof(number_str));
    number_str[index++] = lexer->current;
    lexer_advance(lexer);

    while (lexer->current && (lexer->current == '.' || strchr(DIGITS, lexer->current) != NULL)) {
        if (lexer->current == '.')
            if (++decimal_point_count > 1)
                break;

        number_str[index++] = lexer->current;
        lexer_advance(lexer);
    }

    return & (Token) { NUMBER, strtod(number_str, NULL) };
}

void lexer_advance(Lexer *lexer) {
    lexer->current = lexer->text[lexer->index++];
}
