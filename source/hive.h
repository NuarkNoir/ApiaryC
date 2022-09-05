#pragma once

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

void hive_pop_end(struct Hive* hive);

void hive_remove(struct Hive* hive, struct Honeycomb* node);

bool hive_is_empty(struct Hive* hive);
