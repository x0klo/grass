#include <cutter.h>
#include <lexer.h>

#include <stdio.h>

void test_scan_null();

void test_scan_null()
{
    FILE *program = fopen("test/sample/test/null.txt", "r");
    set_lexer(program);
    cut_assert_null(get_token());
}

void test_scan_w()
{
    FILE *program = fopen("test/sample/test/w.txt", "r");
    set_lexer(program);
    Token *token = get_token();
    cut_assert_true(token->type == SMALL_W);
    cut_assert_true(token->count == 1);
}

void test_scan_W()
{
    FILE *program = fopen("test/sample/test/W.txt", "r");
    set_lexer(program);
    Token *token = get_token();
    cut_assert_true(token->type == LARGE_W);
    cut_assert_true(token->count == 1);
}
