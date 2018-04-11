#ifndef SAY_H
#define SAY_H

#include <stdint.h>

enum {
    BILLION,
    MILLION,
    THOUSAND
};

int say(int64_t n, char **ptr);

#endif