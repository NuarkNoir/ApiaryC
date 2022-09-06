#include <assert.h>
#include <string.h>

#include "lib.h"
#include "hive.h"
#include "melipona.h"

int main()
{
  struct Hive* hive = hive_create();
  assert(hive_is_empty(hive));

  hive_push(hive, "Hello");
  assert(!hive_is_empty(hive));

  hive_push(hive, "world");
  hive_push(hive, "!");
  hive_pop_start(hive);
  hive_reverse(hive);
  assert(strcmp((char*)hive->head->data, "!") == 0);

  hive_destroy(hive);

  return 0;
}
