#ifndef DBG_H
#define DBG_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

/* logging */

#ifdef NDEBUG
#define DBG(Message, ...)
#define ERROR(Message, ...) fprintf(stderr, "ERROR: " Message "%s%s%s\n", ##__VA_ARGS__, (errno == 0 ? "" : " (errno: "), (errno == 0 ? "" : strerror(errno)), (errno == 0 ? "" : ")")); errno = 0
#else
#define DBG(Message, ...) fprintf(stderr, "DEBUG: " Message " (%s:%d)\n", ##__VA_ARGS__, __FILE__, __LINE__)
#define ERROR(Message, ...) fprintf(stderr, "ERROR: " Message " (%s:%d%s%s)\n", ##__VA_ARGS__, __FILE__, __LINE__, (errno == 0 ? "" : ", errno: "), (errno == 0 ? "" : strerror(errno))); errno = 0
#endif

/* assertions */

#define CHECK(Condition, Action, Message, ...) if (!(Condition)) { ERROR(Message, ##__VA_ARGS__); Action }
#define CHECK_DBG(Condition, Message, ...) if (!(Condition)) { DBG(Message, ##__VA_ARGS__); }

#define CHECK_EXIT(Condition, Message, ...) CHECK((Condition), exit(EXIT_FAILURE);, Message, ##__VA_ARGS__)
#define CHECK_MEM(Condition) CHECK_EXIT((Condition), "out of memory")

void print_backtrace(int signum)
{
    pid_t dying_pid = getpid();
    pid_t child_pid = fork();
    if (child_pid < 0) {
        ERROR("fork failed");
    } else if (child_pid == 0) {
        char buf[1024];
        sprintf(buf, "gdb -p %d -batch -ex bt 2>/dev/null | sed '0,/<signal handler/d'", dying_pid);
        const char * argv[] = {"sh", "-c", buf, NULL};
        execve("/bin/sh", (char **)argv, NULL);
        _exit(1);
    } else {
        waitpid(child_pid, NULL, 0);
    }
    _exit(1);
}

void set_sigsegv_handler(void)
{
    CHECK(signal(SIGSEGV, print_backtrace) != SIG_ERR, , "can't set SIGSEGV handler");
}

#endif

