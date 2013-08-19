#include "harness.h"

#include <stdio.h>

#include "test.h"
#include "tests.h"

int run_tests(int timeout);
test_status_t run_test(char * name, test_status_t (*main)(void), int timeout);

int main(int argc, char * argv[])
{
    return run_tests(5000);
}

int run_tests(int timeout)
{
    int total = 0;
    test_entry_t * test;

    for (test = TESTS; test->main; total++, test++);

    int passed = 0;
    int failed = 0;
    int skipped = 0;
    int todo = 0;
    int current = 1;

    for (test = TESTS; test->main; test++, current++) {
        switch (run_test(test->name, test->main, timeout)) {
        case TEST_OK:
            passed++;
            break;
        case TEST_SKIP:
            skipped++;
            break;
        case TEST_TODO:
            todo++;
            break;
        default:
            failed++;
            break;
        }
    }

    printf("\n%d total, %d passed, %d failed, %d skipped, %d todo\n", total, passed, failed, skipped, todo);

    return passed != total;
}

test_status_t run_test(char * name, test_status_t (*main)(void), int timeout)
{
    // TODO timeout
    // TODO crash safely

    test_status_t test_status = main();
    if (test_status != TEST_FAIL) {
        printf("%s", ".");
        fflush(stdout);
    } else {
        fprintf(stderr, "\n%s failed.\n", name);
        fflush(stderr);
    }

    return test_status;
}

