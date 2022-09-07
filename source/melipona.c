#include "melipona.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Plane* plane_create(int len, int cap, int spd, int dist, char* dest)
{
  struct Plane* plane = (struct Plane*)malloc(sizeof(struct Plane) + sizeof(int)*5 + sizeof(char*));
  plane->__struct_id = 0;
  plane->len = len;
  plane->cap = cap;
  plane->spd = spd;
  plane->dist = dist;
  plane->dest = dest;
  return plane;
}

struct Train* train_create(int cnt, int spd, int dist, char* dest)
{
  struct Train* train = (struct Train*)malloc(sizeof(struct Train) + sizeof(int)*4 + sizeof(char*));
  train->__struct_id = 1;
  train->cnt = cnt;
  train->spd = spd;
  train->dist = dist;
  train->dest = dest;
  return train;
}

struct Boat* boat_create(int disp, int year, int spd, int dist, char* dest)
{
  struct Boat* boat = (struct Boat*)malloc(sizeof(struct Boat) + sizeof(int)*5 + sizeof(char*));
  boat->__struct_id = 2;
  boat->disp = disp;
  boat->year = year;
  boat->spd = spd;
  boat->dist = dist;
  boat->dest = dest;
  return boat;
}

bool is_plane(void* obj)
{
  return ((struct Plane*)obj)->__struct_id == 0;
}

bool is_train(void* obj)
{
  return ((struct Train*)obj)->__struct_id == 1;
}

bool is_boat(void* obj)
{
  return ((struct Boat*)obj)->__struct_id == 2;
}

char** common_attrs = (char*[]) { "spd", "dist", "dest", NULL};
char** plane_attrs = (char*[]) { "len", "cap", NULL};
char** train_attrs = (char*[]) { "cnt", NULL};
char** boat_attrs = (char*[]) { "disp", "year", NULL};

bool is_plane_attr(char* attr)
{
  for (int i = 0; plane_attrs[i] != NULL; i++) {
    if (strcmp(attr, plane_attrs[i]) == 0) {
      return true;
    }
  }
  return false;
}

bool is_train_attr(char* attr)
{
  for (int i = 0; train_attrs[i] != NULL; i++) {
    if (strcmp(attr, train_attrs[i]) == 0) {
      return true;
    }
  }
  return false;
}

bool is_boat_attr(char* attr)
{
  for (int i = 0; boat_attrs[i] != NULL; i++) {
    if (strcmp(attr, boat_attrs[i]) == 0) {
      return true;
    }
  }
  return false;
}

bool is_attr(char* attr)
{
  for (int i = 0; common_attrs[i] != NULL; i++) {
    if (strcmp(common_attrs[i], attr) == 0) {
      return true;
    }
  }
  return is_plane_attr(attr) || is_train_attr(attr) || is_boat_attr(attr);
}

bool has_attr(void* obj, char* attr)
{
  if (is_plane(obj)) {
    return is_plane_attr(attr);
  } else if (is_train(obj)) {
    return is_train_attr(attr);
  }
  return is_attr(attr);
}

void* get_plane_attr(struct Plane* plane, char* attr)
{
  if (strcmp(attr, "len") == 0) {
    return &plane->len;
  } else if (strcmp(attr, "cap") == 0) {
    return &plane->cap;
  } else if (strcmp(attr, "spd") == 0) {
    return &plane->spd;
  } else if (strcmp(attr, "dist") == 0) {
    return &plane->dist;
  } else if (strcmp(attr, "dest") == 0) {
    return &plane->dest;
  }
  return NULL;
}

void* get_train_attr(struct Train* train, char* attr)
{
  if (strcmp(attr, "cnt") == 0) {
    return &train->cnt;
  } else if (strcmp(attr, "spd") == 0) {
    return &train->spd;
  } else if (strcmp(attr, "dist") == 0) {
    return &train->dist;
  } else if (strcmp(attr, "dest") == 0) {
    return &train->dest;
  }
  return NULL;
}

void* get_boat_attr(struct Boat* boat, char* attr)
{
  if (strcmp(attr, "disp") == 0) {
    return &boat->disp;
  } else if (strcmp(attr, "year") == 0) {
    return &boat->year;
  } else if (strcmp(attr, "spd") == 0) {
    return &boat->spd;
  } else if (strcmp(attr, "dist") == 0) {
    return &boat->dist;
  } else if (strcmp(attr, "dest") == 0) {
    return &boat->dest;
  }
  return NULL;
}

void* get_attr(void* obj, char* attr)
{
  if (is_plane(obj)) {
    return get_plane_attr((struct Plane*)obj, attr);
  } else if (is_train(obj)) {
    return get_train_attr((struct Train*)obj, attr);
  } else if (is_boat(obj)) {
    return get_boat_attr((struct Boat*)obj, attr);
  }
  return NULL;
}

bool attr_eq_int(void* obj, char* attr, int val)
{
  void* attr_val = get_attr(obj, attr);
  if (attr_val == NULL) {
    return false;
  }
  return *(int*)attr_val == val;
}

bool attr_eq_str(void* obj, char* attr, char* val)
{
  void* attr_val = get_attr(obj, attr);
  if (attr_val == NULL) {
    return false;
  }
  return strcmp(*(char**)attr_val, val) == 0;
}
