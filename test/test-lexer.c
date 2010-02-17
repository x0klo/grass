#include <cutter.h>
#include <lexer.h>

#include <stdio.h>

void test_scan_null();

void test_scan_null()
{
    FILE *program = fopen("null.txt", "r");
    set_lexer(program);
    cut_assert_null(get_token());
}
