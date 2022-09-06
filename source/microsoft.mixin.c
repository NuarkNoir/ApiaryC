#ifndef MICROSOFT_MIXIN_H
#define MICROSOFT_MIXIN_H

#include <stddef.h>
#include <stdio.h>

/**
 * @brief Функция считывает строку из некоторого потока stream
 * @note Данная функция не является стандартной для MSVC, поэтому я её взял из компилятора какого-то другого компилятора
 * @param[out] lineptr - указатель на указатель на строку
 * @param[out] n - указатель на размер строки
 * @param[in] stream - поток
 * @return - кол-во прочитанных символов
 */
size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
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
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
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