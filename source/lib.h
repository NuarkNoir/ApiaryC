#pragma once

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
char** read_file(char* filename);

/**
 * @brief Функция разбивает строку на токены
 * @param str - строка
 * @return - указатель на массив строк
 */
char** tokenize(char* str);
