TESTS = run-test.sh
TESTS_ENVIRONMENT = NO_MAKE=yes CUTTER="$(CUTTER)"

noinst_LTLIBRARIES = test_lexer.la

INCLUDES = $(CUTTER_CFLAGS) -I$(top_builddir)/src
LIBS = $(CUTTER_LIBS) $(top_builddir)/src/liblexer.la

LDFLAGS = -module -rpath $(libdir) -avoid-version -no-undefined

test_lexer_la_SOURCES = test-lexer.c

echo-cutter:
	echo $(CUTTER)
