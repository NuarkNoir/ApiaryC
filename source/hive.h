#ifndef HIVE_H
#define HIVE_H

#include <stdbool.h>

/**
 * @brief Структура, описывающая ноду (соту) связного списка (улья)
 */
struct Honeycomb {
  void* data;
  struct Honeycomb* next;
};

/**
 * @brief Структура, описывающая связный список (улей)
 */
struct Hive {
  struct Honeycomb* head;
};

/**
 * @brief Функция создает связный список
 * @return - указатель на созданный список
 */
struct Hive* hive_create();

/**
 * @brief Функция уничтожает связный список
 * @param[in] hive - указатель на список
 */
void hive_destroy(struct Hive* hive);

/**
 * @brief Функция разворачивает связный список
 * @param[in] hive - указатель на список
 */
void hive_reverse(struct Hive* hive);

/**
 * @brief Функция добавляет элемент в конец списка
 * @param[in] hive - указатель на список
 * @param[in] data - указатель на данные
 */
void hive_push(struct Hive* hive, void* data);

/**
 * @brief Функция удаляет элемент из начала списка
 * @param[in] hive - указатель на список
 */
void hive_pop_start(struct Hive* hive);

/**
 * @brief Функция удаляет ноду из списка
 * @param[in] hive - указатель на список
 * @param[in] node - указатель на ноду
 */
void hive_remove(struct Hive* hive, struct Honeycomb* node);

/**
 * @brief Функция возвращает удаляет элемент из списка, если его аттрибут attr относится к data через predicate
 * @note Данная функция специфична для структур, для которых определены соответствующие "is_*" функции
 * @param[in] hive - указатель на список
 * @param[in] attr - аттрибут, по которому происходит сравнение
 * @param[in] predicate - строка, обозначающая предикат
 * @param[in] data - указатель на данные
 */
void hive_remove_if_attr(struct Hive* hive, char* attr, char* predicate, void* data);

/**
 * @brief Функция проверяет, пустой ли список
 * @param[in] hive - указатель на список
 * @return - true, если список пустой, иначе false
 */
bool hive_is_empty(struct Hive* hive);

/**
 * @brief Функция выводит список через функцию, передаваемую printer
 * @param[in] hive - указатель на список
 * @param[in] printer - указатель на функцию, которая выводит элемент списка
 */
void hive_print(struct Hive* hive, void (*printer)(void*));

/**
 * @brief Функция очищает список
 * @param[in] hive - указатель на список
 */
void hive_clear(struct Hive* hive);

/**
 * @brief Функция сортируеь список через функцию, передаваемую comparator по атрибуту attr
 * @note Данная функция специфична для структур, для которых определены соответствующие "is_*" функции, однако реализация comparator может быть любой и учитывать любые атрибуты и/или их наличие
 * @param[in] hive - указатель на список
 * @param[in] attr - атрибут, по которому происходит сортировка
 * @param[in] comparator - указатель на функцию, которая сравнивает элементы списка
 */
void hive_sort(struct Hive* hive, char* attr, bool (*comparator)(char*, void*, void*));

#endif // HIVE_H