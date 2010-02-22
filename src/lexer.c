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
    Type type;
    Type first_type;
    int count;
    Token *token;

    count = 1;
    c = fgetc(program);
    if(c == EOF) {
        token = NULL;
    }
    else {
        token = new_token();
        first_type = get_type(c);
        do {
            c = fgetc(program);
            type = get_type(c);
            if(type == OTHER_CHARACTER) {
                continue;
            }

            if(type == first_type) {
                count++;
            }
            else {
                if(c != EOF) {
                    ungetc(c, program);
                }
            }
        } while(type == first_type && c != EOF);
        set_token(token, first_type, count);
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
    if(c == EOF) {
        return END_OF_FILE;
    }
    else if(c == 'w') {
        return SMALL_W;
    }
    else if(c == 'W') {
        return LARGE_W;
    }
    else if(c == 'v') {
        return SMALL_V;
    }
    else {
        return OTHER_CHARACTER;
    }
}
