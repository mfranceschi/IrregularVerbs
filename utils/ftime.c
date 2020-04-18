//
// Created by Martin on 25/01/2020.
//

#include "ftime_useful_defs.h"

static const useconds_t MICROSECONDS_IN_A_SECOND = (useconds_t)1e6;

#ifdef _WIN32

#include "Utils.h"
#include <windows.h>

int gettimeofday(struct timeval* t, void* tzp) {
    UNUSED(tzp);
    FILETIME ft;
    ULARGE_INTEGER uli;

    GetSystemTimeAsFileTime(&ft);
    uli = (ULARGE_INTEGER) {
            .LowPart = ft.dwLowDateTime,
            .HighPart = ft.dwHighDateTime
    };
    uli.QuadPart /= 10; // we just consider microseconds, not 100 nanoseconds.

    *t = (struct timeval) {
        .tv_usec = uli.QuadPart % MICROSECONDS_IN_A_SECOND,
        .tv_sec = uli.QuadPart / MICROSECONDS_IN_A_SECOND
    };
    return 0;
}

void usleep(useconds_t duration) {
    Sleep(duration / 1000);
}

#else
#include <sys/time.h>

#endif

int64_t timeval_difftime(const struct timeval* a, const struct timeval* b) {
    return
        ((int64_t)(a->tv_sec) - (int64_t)(b->tv_sec)) * MICROSECONDS_IN_A_SECOND +
        ((int64_t)(a->tv_usec) - (int64_t)(b->tv_usec));
}
