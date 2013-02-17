#ifndef DBG_H
#define DBG_H

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define DBG(M, ...)
#else
#define DBG(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define ERR_STR (errno == 0 ? "None" : strerror(errno))

#define LOG_ERR(M, ...) fprintf(stderr, "ERROR (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, ERR_STR, ##__VA_ARGS__)

#define LOG_WARN(M, ...) fprintf(stderr, "WARN (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, ERR_STR, ##__VA_ARGS__)

#define LOG_INFO(M, ...) fprintf(stderr, "INFO (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define CHECK(A, M, ...) if(!(A)) { LOG_ERR(M, ##__VA_ARGS__); errno = 0; goto error; }

#define SENTINEL(M, ...)  { LOG_ERR(M, ##__VA_ARGS__); errno = 0; goto error; }

#define CHECK_MEM(A) CHECK((A), "Out of memory.")

#define CHECK_DBG(A, M, ...) if(!(A)) { DBG(M, ##__VA_ARGS__); errno = 0; goto error; }

#endif
