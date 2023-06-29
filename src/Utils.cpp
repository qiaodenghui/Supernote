#include "Utils.h"
#include <cstring>
#include <cstdlib>
static inline int clampi(int x, int min, int max) {
    return x < min ? min : x > max ? max : x;
}

const char *parsePageRange(const char *s, int *a, int *b, int n) {
    if (!s || !s[0]) {
        return nullptr;
    }

    if (s[0] == ',') {
        s += 1;
    }

    if (s[0] == 'N') {
        *a = n;
        s += 1;
    } else {
        *a = strtol(s, (char **)&s, 10);
    }

    if (s[0] == '-') {
        if (s[1] == 'N') {
            *b = n;
            s += 2;
        } else {
            *b = strtol(s + 1, (char **)&s, 10);
        }
    } else {
        *b = *a;
    }

    if (*a < 0) {
        *a = n + 1 + *a;
    }
    if (*b < 0) {
        *b = n + 1 + *b;
    }

    *a = clampi(*a, 1, n);
    *b = clampi(*b, 1, n);

    return s;
}
