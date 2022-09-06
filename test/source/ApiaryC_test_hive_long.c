#include <assert.h>
#include <string.h>

#include "lib.h"
#include "hive.h"
#include "melipona.h"

int main()
{
  struct Hive* hive = hive_create();
  assert(hive_is_empty(hive));
  
  char** combs = (char*[]){"ab", "bc", "cd", "0.0", "2", "-1", NULL};
  for (int i = 0; combs[i] != NULL; i++) {
    hive_push(hive, combs[i]);
  }
  hive_reverse(hive);
  assert(strcmp((char*)hive->head->data, "-1") == 0);
  assert(strcmp((char*)hive->head->next->data, "2") == 0);
  hive_reverse(hive);
  assert(strcmp((char*)hive->head->data, "ab") == 0);
  assert(strcmp((char*)hive->head->next->data, "bc") == 0);

  return 0;
}
