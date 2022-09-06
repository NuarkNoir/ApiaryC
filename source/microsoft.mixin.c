#ifndef MICROSOFT_MIXIN_H
#define MICROSOFT_MIXIN_H

#include <stddef.h>
#include <stdio.h>

size_t getline(char **lineptr, size_t *n, FILE *stream) { // NOLINT
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1; // NOLINT
    }
    if (stream == NULL) {
        return -1; // NOLINT
    }
    if (n == NULL) {
        return -1; // NOLINT
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) { // NOLINT
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1; // NOLINT
            }
        }
        *p++ = c; // NOLINT
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}

#endif // MICROSOFT_MIXIN_H