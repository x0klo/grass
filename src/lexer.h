#ifndef LEXER_H

#include <stdio.h>

typedef enum {
    SMALL_W,
    LARGE_W
} TYPE;

typedef struct {
    TYPE type;
    int  count;
} Token;

void set_lexer(FILE *program);
Token *get_token();

#endif // LEXER_H
