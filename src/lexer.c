#include <lexer.h>

#include <stdlib.h>

static Token *new_token();
static void set_token(Token *token, Type type, int count);
static Type get_type(int c);

static FILE *program;

void set_lexer(FILE *p)
{
    program = p;
}

Token *get_token()
{
    int c;
    int first_c;
    Type type;
    int count;
    Token *token = new_token();

    count = 1;
    c = fgetc(program);
    if(c == EOF) {
        token = NULL;
    }
    else {
        first_c = c;
        type = get_type(c);
        do {
            c = fgetc(program);
            if(c == first_c) {
                count++;
            }
            else {
                ungetc(c, program);
            }
        } while(c == first_c);
        set_token(token, type, count);
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

static Type get_type(int c)
{
    if(c == 'w') {
        return SMALL_W;
    }
    else if(c == 'W') {
        return LARGE_W;
    }
    else {
        return SMALL_V;
    }
}
