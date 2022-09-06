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
  struct Honeycomb* prev = NULL;
  struct Honeycomb* current = hive->head;
  struct Honeycomb* next = NULL;
  
  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  
  hive->head = prev;
}

void hive_push(struct Hive* hive, void* data)
{
  struct Honeycomb* comb = (struct Honeycomb*)malloc(sizeof(struct Honeycomb));
  comb->data = data;
  comb->next = hive->head;
  hive->head = comb;
}

void hive_pop_start(struct Hive* hive)
{
  struct Honeycomb* comb = hive->head;
  hive->head = comb->next;
  free(comb);
}

void hive_pop_end(struct Hive* hive)
{
  struct Honeycomb* comb = hive->head;
  if (comb->next == NULL) {
    hive_pop_start(hive);
    return;
  }
  struct Honeycomb* prev = NULL;
  while (comb->next != NULL) {
    prev = comb;
    comb = comb->next;
  }
  if (prev != NULL) {
    prev->next = NULL;
  }
  free(comb);
}

void hive_remove(struct Hive* hive, struct Honeycomb* node)
{
  struct Honeycomb* comb = hive->head;
  if (comb == node) {
    hive_pop_start(hive);
    return;
  }
  struct Honeycomb* prev = NULL;
  while (comb != NULL) {
    if (comb == node) {
      prev->next = comb->next;
      free(comb);
      return;
    }
    prev = comb;
    comb = comb->next;
  }
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
  struct Honeycomb* prev = NULL;
  while (comb != NULL) {
    if (_hive_remove_if_attr_predicate(attr, predicate, comb->data, data)) {
      if (prev == NULL) {
        hive_pop_start(hive);
        comb = hive->head;
      } else {
        prev->next = comb->next;
        free(comb);
        comb = prev->next;
      }
    } else {
      prev = comb;
      comb = comb->next;
    }
  }
}

bool hive_is_empty(struct Hive* hive)
{
  return hive->head == NULL;
}

void hive_print(struct Hive* hive, void (*printer)(void*))
{
  struct Honeycomb* comb = hive->head;
  while (comb != NULL) {
    (*printer)(comb->data);
    comb = comb->next;
  }
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
  while (comb != NULL) {
    struct Honeycomb* next = comb->next;
    while (next != NULL) {
      if ((*comparator)(attr, comb->data, next->data)) {
        void* temp = comb->data;
        comb->data = next->data;
        next->data = temp;
      }
      next = next->next;
    }
    comb = comb->next;
  }
}
