#ifndef MELIPONA_H
#define MELIPONA_H

#include <stdbool.h>
#include <stddef.h>
#include "hive.h"

/**
 * @brief Структура, описывающая самолёт
 */
struct Plane {
    int __struct_id; 
    int len; ///< flight length
    int cap; ///< capacity
    int spd; ///< speed
    int dist; ///< distance
    char* dest; ///< destination
};

/**
 * @brief Структура, описывающая поезд
 */
struct Train {
    int __struct_id;
    int cnt; ///< vagon count
    int spd; ///< speed
    int dist; ///< distance
    char* dest; ///< destination
};

/**
 * @brief Функция, создающая самолёт
 * @param[in] len - flight length
 * @param[in] cap - capacity
 * @param[in] spd - speed
 * @param[in] dist - distance
 * @param[in] dest - destination
 * @return - указатель на структуру Plane
 */
struct Plane* plane_create(int len, int cap, int spd, int dist, char* dest);
/**
 * @brief Функция, создающая поезд
 * @param[in] cnt - vagon count
 * @param[in] spd - speed
 * @param[in] dist - distance
 * @param[in] dest - destination
 * @return - указатель на структуру Train
 */
struct Train* train_create(int cnt, int spd, int dist, char* dest);

/**
 * @brief Функция, проверяющая тип объекта на соответствие Plane
 * @param[in] obj - указатель на объект
 * @return - true, если объект Plane, иначе false
 */
bool is_plane(void* obj);
/**
 * @brief Функция, проверяющая тип объекта на соответствие Train
 * @param[in] obj - указатель на объект
 * @return - true, если объект Train, иначе false
 */
bool is_train(void* obj);

/**
 * @brief Функция, проверяющая аттрибут на налиичие в структуре Plane
 * @param[in] attr - аттрибут
 * @return - true, если это аттрибут Plane, иначе false
 */
bool is_plane_attr(char* attr);
/**
 * @brief Функция, проверяющая аттрибут на налиичие в структуре Train
 * @param[in] attr - аттрибут
 * @return - true, если это аттрибут Train, иначе false
 */
bool is_train_attr(char* attr);
/**
 * @brief Функция, проверяющая аттрибут на налиичие в структуре Plane, или Train, или других
 * @param[in] attr - аттрибут
 * @return - true, если это аттрибут Plane, или Train, или других, иначе false
 */
bool is_attr(char* attr);
/**
 * @brief Функция, проверяющая аттрибут на налиичие в структуре
 * @param[in] obj - указатель на объект
 * @param[in] attr - аттрибут
 * @return - true, если этот аттрибут имеется, иначе false
 */
bool has_attr(void* obj, char* attr);
/**
 * @brief Функция, возвращающая значение аттрибута
 * @param[in] obj - указатель на объект
 * @param[in] attr - аттрибут
 * @return - указатель значение аттрибута или NULL, если аттрибут не найден
 */
void* get_attr(void* obj, char* attr);
/**
 * @brief Функция, проверяющая аттрибут на равенство целому числу
 * @param[in] obj - указатель на объект
 * @param[in] attr - аттрибут
 * @param[in] val - значение
 * @return - true, если аттрибут равен значению, иначе false
 */
bool attr_eq_int(void* obj, char* attr, int val);
/**
 * @brief Функция, проверяющая аттрибут на равенство строке
 * @param[in] obj - указатель на объект
 * @param[in] attr - аттрибут
 * @param[in] val - значение
 * @return - true, если аттрибут равен значению, иначе false
 */
bool attr_eq_str(void* obj, char* attr, char* val);

#endif // MELIPONA_H