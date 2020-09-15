#ifndef LEXER_H
#define LEXER_H

#include "tokens.h"

#define WHITESPACE " \n\t"
#define DIGITS "0123456789"

typedef struct Lexer {
    const char *text;
    char error[50];
    char current;
    int text_size;
    int index;
} Lexer;

Tokens *lexer_get_tokens(Lexer *, const char *, int);
Token *lexer_get_number(Lexer *);
void lexer_advance(Lexer *);

#endif // LEXER_H
