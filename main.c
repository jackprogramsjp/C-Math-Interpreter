#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokens.h"
#include "lexer.h"
#include "nodes.h"
#include "parser.h"
#include "interpreter.h"
#include "values.h"

int main(void) {
    char buff[256];

    printf("calc > ");

    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        buff[strcspn(buff, "\n")] = 0;

        if (!*buff) {
            printf("calc > ");
            continue;
        }

        Lexer lexer;
        Tokens *tokens = lexer_get_tokens(&lexer, buff, sizeof(buff));

        if (tokens != NULL) {
            //print_tokens(tokens);
        }

        if (*lexer.error) {
            fprintf(stderr, "%s\n", lexer.error);
            printf("calc > ");
            continue;
            // If there is an error, the lexer actually frees the tokens for you
        }

        Parser parser;
        Node *tree;

        if (tokens != NULL)  {
            tree = parser_parse(&parser, &tokens);

            if (tokens != NULL && !*parser.error) {
                free_tokens(tokens);
                tokens = NULL;
            }
        }

        if (tree != NULL) {
            //print_node(tree); putchar('\n');
        }

        if (*parser.error && !*lexer.error) {
            fprintf(stderr, "%s\n", parser.error);
            tokens = NULL;
            printf("calc > ");
            continue;
            // If there is an error, the parser actually frees the nodes for you
        }

        if (tree != NULL) {
            Interpreter interpreter;
            Number result = interpreter_visit(&interpreter, tree);

            if (interpreter.error == NULL && !*parser.error) {
                print_number(&result);
            } else {
                fprintf(stderr, "%s\n", interpreter.error);
            }

            if (tree != NULL) {
                free_node(tree);
                tree = NULL;
            }
        }

        printf("calc > ");
    }

    return 0;
}
