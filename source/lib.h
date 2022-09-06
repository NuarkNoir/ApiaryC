#ifndef PARSER_LIB_H
#define PARSER_LIB_H

#include "hive.h"

/**
 * @brief Функция убирает пробельные символы в начале и конце строки
 * @param str - строка
 * @return строка без пробельных символов
 */
char* trim(char* str);

/**
 * @brief Функция считывает файл построчно и возвращает указатель на массив строк
 * @param filename - имя файла
 * @return - указатель на массив строк
 */
char** read_file(const char* filename);

/**
 * @brief Функция разбивает строку на токены
 * @param str - строка
 * @return - указатель на массив строк
 */
char** tokenize(char* str);

void parse_line(char** tokens, struct Hive* hive);

#endif // PARSER_LIB_H