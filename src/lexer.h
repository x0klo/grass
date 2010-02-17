#ifndef LEXER_H

#include <stdio.h>

typedef struct {
} Token;

void set_lexer(FILE *program);
Token *get_token();

#endif // LEXER_H
