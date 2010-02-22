#include <lexer.h>

#include <stdlib.h>

static Token *new_token();
static void set_token(Token *token, Type type, int count);
static Type char2type(int c);
static int type2char(Type t);
static Type get_type();

static FILE *program;

void set_lexer(FILE *p)
{
    program = p;
}

Token *get_token()
{
    Type type;
    Type first_type;
    int count;
    Token *token;

    type = get_type();
    if(type == END_OF_FILE) {
        token = NULL;
    }
    else {
        count = 1;
        token = new_token();
        first_type = type;
        do {
            type = get_type();
            if(type == first_type) {
                count++;
            }
            else if(type != END_OF_FILE) {
                ungetc( type2char(type), program);
            }
        } while(type == first_type && type != END_OF_FILE);
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

static Type char2type(int c)
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

static int type2char(Type t)
{
    if(t == END_OF_FILE) {
        return EOF;
    }
    else if(t == SMALL_W) {
        return 'w';
    }
    else if(t == LARGE_W) {
        return 'W';
    }
    else if(t == SMALL_V) {
        return 'v';
    }
    else {
        return ' ';
    }
}

static Type get_type()
{
    int c;
    Type type;

    do {
        c = fgetc(program);
        type = char2type(c);
        if(type == OTHER_CHARACTER) {
            continue;
        }
    } while(type == OTHER_CHARACTER);

    return type;
}
