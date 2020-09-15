#ifndef TOKENS_H
#define TOKENS_H

typedef enum {
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    POWER,
    EOF_
} TokenType;

typedef struct Token {
    TokenType type;
    double value;
} Token;

typedef struct Tokens {
    Token token;
    struct Tokens *next;
} Tokens;

const char *format_token_type(TokenType);
void print_token(Token *); // Pointer because I want the struct, not the copy of it
void append_tokens(Tokens **, Token);
Token *index_tokens(Tokens **, int);
void print_tokens(Tokens *);
void free_tokens(Tokens *);

#endif // TOKENS_H
