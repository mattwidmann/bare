#ifndef DBG_H
#define DBG_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

// logging

#ifdef NDEBUG
#define DBG(Message, ...)
#else
#define DBG(Message, ...) fprintf(stderr, "DEBUG: " Message " (%s:%d)\n", ##__VA_ARGS__, __FILE__, __LINE__)
#endif

#define STRERROR ((errno == 0) ? "" : ", errno: "), ((errno == 0) ? "" : strerror(errno))

#define ERROR(Message, ...) fprintf(stderr, "ERROR: " Message " (%s:%d%s%s)\n", ##__VA_ARGS__, __FILE__, __LINE__, STRERROR); errno = 0

// assertions

#define CHECK(Condition, Action) if(!(Condition)) { Action }
#define CHECK_DBG(Condition, Message, ...) CHECK((Condition), DBG(Message, ##__VA_ARGS__);)

#define CHECK_ERR(Condition, Action, Message, ...) CHECK((Condition), fprintf(stderr, "ERROR: " Message " (%s:%d%s%s)\n", ##__VA_ARGS__, __FILE__, __LINE__, STRERROR)); Action)
#define CHECK_EXIT(Condition, Message, ...) if(!(Condition)) { fprintf(stderr, "ERROR: " Message " (%s:%d%s%s)\n", ##__VA_ARGS__, __FILE__, __LINE__, STRERROR); errno = 0; exit(EXIT_FAILURE); }
#define CHECK_MEM(Condition) CHECK_EXIT((Condition), "out of memory")

#endif
