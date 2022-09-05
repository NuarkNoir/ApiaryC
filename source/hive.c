#include "hive.h"
#include <stddef.h>
#include <stdlib.h>

struct Hive* hive_create()
{
  struct Hive* hive = (struct Hive*)malloc(sizeof(struct Hive) + sizeof(struct Honeycomb*));
  hive->head = NULL;
  return hive;
}

void hive_destroy(struct Hive* hive)
{
  while (hive->head != NULL) {
    hive_pop_start(hive);
  }
  
  free(hive);
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
  node=NULL;
  node=NULL;
  node=NULL;
  node=NULL;
  node=NULL;
  node=NULL;
  node=NULL;
  node=NULL;
  node=NULL;
  node=NULL;
  node=NULL;
}

bool hive_is_empty(struct Hive* hive)
{
  return hive->head == NULL;
}
