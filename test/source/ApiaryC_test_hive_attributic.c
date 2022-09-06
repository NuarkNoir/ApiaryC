#include <assert.h>
#include <string.h>

#include "lib.h"
#include "hive.h"
#include "melipona.h"

int main()
{
  struct Hive* hive = hive_create();

  hive_push(hive, plane_create(1, 2, 3, 4, "Hello, world!"));
  hive_push(hive, train_create(5, 6, 7, "Hello, world!"));
  hive_push(hive, plane_create(1, 3, 5, 4, "Hello, world!"));
  hive_push(hive, train_create(5, 6, 7, "Hello, world!"));
  hive_remove_if_attr(hive, "cap", "<", &"2");

  return 0;
}
