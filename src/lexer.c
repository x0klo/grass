#include <lexer.h>

#include <stdlib.h>

static Token *new_token();
static void set_token(Token *token, Type type, int count);

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
        token = NULL;
    }
    else if(c == 'w') {
        set_token(token, SMALL_W, 1);
    }
    else if(c == 'W') {
        set_token(token, LARGE_W, 1);
    }
    else if(c == 'v') {
        set_token(token, SMALL_V, 1);
    }

    return token;
}

static Token *new_token()
{
    return malloc(sizeof(Token));
}

static void set_token(Token *token, Type type, int count)
{
    token->type = type;
    token->count = count;
}
