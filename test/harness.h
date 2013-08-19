#ifndef HARNESS_H
#define HARNESS_H

#include "test.h"

typedef struct {
    char * name;
    test_status_t (*main)(void);
    int silence;
} test_entry_t;

#define TEST_LIST_START test_entry_t TESTS[] = {
#define TEST_ENTRY(Name) { #Name, test_##Name, 0 },
#define TEST_LIST_END {NULL, NULL, 0} };

#define TEST_DECLARE(Name) test_status_t TEST_NAME(Name)(void);

extern test_entry_t TESTS[];

#endif
