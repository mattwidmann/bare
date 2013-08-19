#ifndef TEST_H
#define TEST_H

#include <stdlib.h>

typedef enum {
    TEST_OK = 0,
    TEST_FAIL,
    TEST_SKIP,
    TEST_TODO
} test_status_t;

#define TEST_NAME(Name) test_##Name
#define TEST_DEFINE(Name) test_status_t TEST_NAME(void)

#define LOG(...) do { \
    fprintf(stderr, "%s", __VA_ARGS__); \
    fflush(stderr); \
} while (0)

#define LOGF(...) do { \
    fprintf(stderr, __VA_ARGS__); \
    fflush(stderr); \
} while (0)

#define FATAL(Message) do { \
    fprintf(stderr, "FATAL: %s:%d: %s\n", __FILE__, __LINE__, Message); \
    fflush(stderr); \
    abort(); \
} while (0)

#define ASSERT(Condition) do { \
    if (!(Condition)) { \
        fprintf(stderr, "ASSERT: %s:%d: %s\n", __FILE__, __LINE__, #Condition); \
        fflush(stderr); \
        abort(); \
    } \
} while (0)

#define TEST(Condition) do { \
    if (!(Condition)) { \
        return TEST_FAIL; \
    } \
} while (0)

#endif

