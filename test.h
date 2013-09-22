#ifndef TST_H
#define TST_H

#include <signal.h>
#include <setjmp.h>
#include <stdio.h>
#include <assert.h>

int MW_test_passed_tests = 0;
int MW_test_current_test = 0;
jmp_buf MW_test_jmp;

static void MW_test_handle_sigabrt(int nothing)
{
    longjmp(MW_test_jmp, 1);
}

#define RUN_TEST(message, test) do { \
        printf("TEST %d: %c[;%dm\"%s\"%c[0m ... ", MW_test_current_test, 0x1B, 34, message, 0x1B); \
        signal(SIGABRT, MW_test_handle_sigabrt); \
        MW_test_current_test++; \
        if (setjmp(MW_test_jmp) == 0) { \
            test; \
            MW_test_passed_tests++; \
            printf("%c[;%dmOK%c[0m\n", 0x1B, 32, 0x1B); \
        } else { \
            printf("%c[;%dmFAILED%c[0m\n", 0x1B, 31, 0x1B); \
        } \
        fflush(stdin); \
    } while (0)

#define END_TESTS() do { \
        printf("%d tests run, %d passed, %d failed\n", MW_test_current_test, MW_test_passed_tests, MW_test_current_test - MW_test_passed_tests); \
        MW_test_current_test = 0; \
        MW_test_passed_tests = 0; \
    } while (0)

#endif

