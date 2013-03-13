#ifndef DBG_H
#define DBG_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

// logging

#define MESSAGE(Prefix, Message) Prefix ": " Message "\n"

#ifdef NDEBUG
#define DBG(Message, ...)
#else
#define DBG(Message, ...) fprintf(stderr, MESSAGE("DEBUG", Message " (%s:%d)"), ##__VA_ARGS__, __FILE__, __LINE__)
#endif

#define ERROR(Message, ...) fprintf(stderr, MESSAGE("ERROR", Message " (%s:%d%s%s)"), ##__VA_ARGS__, __FILE__, __LINE__, (errno == 0 ? "" : ", errno: "), (errno == 0 ? "" : strerror(errno))); errno = 0

// assertions

#define CHECK(Condition, Action, Message, ...) if (!(Condition)) { ERROR((Message), ##__VA_ARGS__); Action }
#define CHECK_DBG(Condition, Message, ...) if (!(Condition)) { DBG((Message), ##__VA_ARGS__); }

#define CHECK_EXIT(Condition, Message, ...) CHECK((Condition), exit(EXIT_FAILURE);, (Message), ##__VA_ARGS__)
#define CHECK_MEM(Condition) CHECK_EXIT((Condition), "out of memory")

#endif
