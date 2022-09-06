#ifndef HIVE_H
#define HIVE_H

#include <stdbool.h>

struct Honeycomb {
  void* data;
  struct Honeycomb* next;
};

struct Hive {
  struct Honeycomb* head;
};

struct Hive* hive_create();

void hive_destroy(struct Hive* hive);

void hive_reverse(struct Hive* hive);

void hive_push(struct Hive* hive, void* data);

void hive_pop_start(struct Hive* hive);

void hive_remove(struct Hive* hive, struct Honeycomb* node);

void hive_remove_if_attr(struct Hive* hive, char* attr, char* predicate, void* data);

bool hive_is_empty(struct Hive* hive);

void hive_print(struct Hive* hive, void (*printer)(void*));

void hive_clear(struct Hive* hive);

void hive_sort(struct Hive* hive, char* attr, bool (*comparator)(char*, void*, void*));

#endif // HIVE_H