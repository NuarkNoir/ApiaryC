#include "hive.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "melipona.h"

struct Hive* hive_create()
{
  struct Hive* hive = (struct Hive*)malloc(sizeof(struct Hive) + sizeof(struct Honeycomb*));
  hive->head = NULL;
  return hive;
}

void hive_destroy(struct Hive* hive)
{
  hive_clear(hive);  
  free(hive);
}

void hive_reverse(struct Hive* hive)
{
  if (hive->head == NULL) return;
  struct Honeycomb* old_first = hive->head;
  struct Honeycomb* prev = NULL;
  struct Honeycomb* current = hive->head;
  struct Honeycomb* next = NULL;
  
  do {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  } while (current != hive->head);
  
  hive->head = prev;
  old_first->next = hive->head;
}

void hive_push(struct Hive* hive, void* data)
{
  struct Honeycomb* comb = (struct Honeycomb*)malloc(sizeof(struct Honeycomb) + sizeof(void*));
  comb->data = data;
  if (hive->head == NULL) {
    comb->next = comb;
    hive->head = comb;
  } else if (hive->head->next == hive->head) {
    hive->head->next = comb;
    comb->next = hive->head;
  } else {
    struct Honeycomb* last = hive->head->next;
    while (last->next != hive->head) {
      last = last->next;
    }
    last->next = comb;
    comb->next = hive->head;
  }
}

void hive_pop_start(struct Hive* hive)
{
  if (hive->head == NULL) return;
  if (hive->head == hive->head->next) {
    free(hive->head);
    hive->head = NULL;
  } else {
    struct Honeycomb* last = hive->head->next;
    while (last->next != hive->head) {
      last = last->next;
    }
    struct Honeycomb* comb = hive->head;
    hive->head = hive->head->next;
    last->next = hive->head;
    free(comb);
  }
}

void hive_remove(struct Hive* hive, struct Honeycomb* node)
{
  struct Honeycomb* comb = hive->head;
  if (comb == NULL) return;
  if (comb == node) {
    hive_pop_start(hive);
    return;
  }
  struct Honeycomb* prev = NULL;
  do {
    if (comb == node) {
      prev->next = comb->next;
      free(comb);
      return;
    }
    prev = comb;
    comb = comb->next;
  } while (comb != hive->head);
}

bool _hive_remove_if_attr_predicate(char* attr, char* predicate, void* data, void* expected) 
{
  void* attrVal = get_attr(data, attr);
  if (attrVal == NULL) return false;
  if (strcmp(attr, "dest") == 0) {
    int cval = strcmp(*(char**)attrVal, expected);
    return strcmp(predicate, "=") == 0 ? (cval == 0) : (cval != 0);
  }
  int attrInt = *(int*)attrVal;
  int expectedInt = atoi(expected);
  if (strcmp(predicate, ">") == 0) {
    return attrInt > expectedInt;
  } else if (strcmp(predicate, "<") == 0) {
    return attrInt < expectedInt;
  } else if (strcmp(predicate, "=") == 0) {
    return attrInt == expectedInt;
  }
  return attrInt != expectedInt;
}

void hive_remove_if_attr(struct Hive* hive, char* attr, char* predicate, void* data)
{
  struct Honeycomb* comb = hive->head;
  if (comb == NULL) return;
  struct Honeycomb* prev = NULL;
  do {
    while (hive->head != NULL && _hive_remove_if_attr_predicate(attr, predicate, comb->data, data)) {
      struct Honeycomb* next = comb->next;
      hive_remove(hive, comb);
      comb = next;
    }
    if (hive->head == NULL) return;
    comb = comb->next;
  } while (comb != hive->head);
}

bool hive_is_empty(struct Hive* hive)
{
  return hive->head == NULL;
}

void hive_print(struct Hive* hive, void (*printer)(void*))
{
  struct Honeycomb* comb = hive->head;
  if (comb == NULL) return;
  do {
    (*printer)(comb->data);
    comb = comb->next;
  } while (comb != hive->head);
}

void hive_clear(struct Hive* hive)
{
  while (hive->head != NULL) {
    hive_pop_start(hive);
  }
}

void hive_sort(struct Hive* hive, char* attr, bool (*comparator)(char*, void*, void*))
{
  struct Honeycomb* comb = hive->head;
  if (comb == NULL) return;
  do {
    struct Honeycomb* next = comb->next;
    while (next != hive->head) {
      if ((*comparator)(attr, comb->data, next->data)) {
        void* temp = comb->data;
        comb->data = next->data;
        next->data = temp;
      }
      next = next->next;
    }
    comb = comb->next;
  } while (comb != hive->head);
}
