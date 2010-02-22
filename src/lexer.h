#ifndef LEXER_H

#include <stdio.h>

typedef enum {
    END_OF_FILE,
    SMALL_W,
    LARGE_W,
    SMALL_V,
    OTHER_CHARACTER
} Type;

typedef struct {
    Type type;
    int  count;
} Token;

void set_lexer(FILE *program);
Token *get_token();

#endif // LEXER_H
