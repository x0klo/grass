#include <lexer.h>

#include <stdlib.h>

static Token *new_token();

static FILE *program;

void set_lexer(FILE *p)
{
    program = p;
}

Token *get_token()
{
    char c;
    Token *token = new_token();

    c = fgetc(program);
    if(c == EOF) {
        return NULL;
    }
    else if(c == 'w') {
        token->type = SMALL_W;
        token->count = 1;
        return token;
    }
    else if(c == 'W') {
        token->type = LARGE_W;
        token->count = 1;
        return token;
    }
}

static Token *new_token()
{
    return malloc(sizeof(Token));
}
