#pragma once

#include <stdbool.h>
#include <stddef.h>
#include "hive.h"

struct Plane {
    int __struct_id;
    int len; // flight length
    int cap; // capacity
    int spd; // speed
    int dist; // distance
    char* dest; // destination
};

struct Train {
    int __struct_id;
    int cnt; // vagon count
    int spd; // speed
    int dist; // distance
    char* dest; // destination
};

struct Plane* plane_create(int len, int cap, int spd, int dist, char* dest);
struct Train* train_create(int cnt, int spd, int dist, char* dest);

bool is_plane(void* obj);
bool is_train(void* obj);

bool is_plane_attr(char* attr);
bool is_train_attr(char* attr);
bool is_attr(char* attr);
bool has_attr(void* obj, char* attr);
void* get_attr(void* obj, char* attr);
bool attr_eq_int(void* obj, char* attr, int val);
bool attr_eq_str(void* obj, char* attr, char* val);
